#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <iostream>
#include "hw5.h"

//constructor
game::game(QWidget *parent) : QWidget(parent)
{
  lives = 3;
  score = 0;
  level = 1;
  killsleft = 0;
  gameover = false;
  gamestarted = false;
  was_hit = false;
  blink = false;
  transitioning = false;
  minions = true;
  timerswing = 200;
  timerimmune = 3000;
  playerswing = false;
  background.load("images/level1.png");
  playerobj = new player(QString("images/player.png"), this);
}

//deconstructor
game::~game()
{
    while (!enemy.isEmpty())
        delete enemy.takeFirst();
    while (!obstacle.isEmpty())
        delete obstacle.takeFirst();
    while (!bullet.isEmpty())
        delete bullet.takeFirst();
    delete playerobj;
}

//paint event
void game::paintEvent(QPaintEvent *event) //draw and paint
{
  QPainter painter(this);
  if (gameover == true) //paint gameover screen
    {
      if (!transitioning)
      {
          QFont font("Courier", 15, QFont::DemiBold);
          QFontMetrics gameoverfont(font);
          int textWidth = gameoverfont.width("Game Over, click to restart");

          painter.setFont(font);

          painter.translate(QPoint(width()/2,height()/2));
          painter.drawText(-textWidth/2, 0, "Game Over, click to restart");
      }
      else
      {
          QFont font("Courier", 15, QFont::DemiBold);
          QFontMetrics gameoverfont(font);
          int textWidth = gameoverfont.width("You have defeated the Lich King!");
          int textWidth2 = gameoverfont.width("Click to restart");

          painter.setFont(font);

          painter.translate(QPoint(width()/2,height()/2));
          painter.drawText(-textWidth/2, 0, "You have defeated the Lich King!");
          painter.translate(QPoint(0,30));
          painter.drawText(-textWidth2/2, 0,  "Click to restart");
          painter.translate(QPoint(0,30));
          QString finalview = QString("Score: %2").arg(score);
          textWidth = gameoverfont.width(finalview);
          painter.drawText(-textWidth/2, 0, finalview);
      }
    }
  else
    {
      //paint level background
      painter.drawImage(background.rect(), background);
      //paint status
      QFont font("Courier", 12, QFont::DemiBold);
      QFontMetrics status(font);
      int textheight = status.height();
      painter.setFont(font);

      QString statustext = QString("Lives: %1 Score: %2").arg(lives).arg(score);
      
      painter.drawText(0, textheight/2, statustext);
      if (gamestarted == true && transitioning == false) //paint all entities
      {
          //paint all obstacles
          for (int i = 0; i < obstacle.size(); i++)
          {
              character *obj = obstacle.at(i);
              painter.drawImage(obj->getRect(), obj->getImage());
          }
          //paint all enemies
          for (int i = 0; i < enemy.size(); i++)
          {
              character *obj = enemy.at(i);
              painter.drawImage(obj->getRect(), obj->getImage());
          }
          for (int i = 0; i < bullet.size(); i++)
          {
              projectile *obj = bullet.at(i);
              painter.drawImage(obj->getRect(), obj->getImage());
          }
          //paint player, will make it blink when hit
          if (!blink)
          {
            painter.drawImage(playerobj->getRect(),playerobj->getImage());
          }
          //immune timer and blinker
          if (was_hit)
          {
              blink = !blink;
          }
          //swing timer and paints player swing briefly
          if (playerswing)
          {
              painter.drawImage(playerobj->getAttackRect(), playerobj->getAttackImage());
          }
      }
      else //paint intro screen
	{
          if (!transitioning)
          {
              QString instructtext = QString("Fight your way inland!");
              QString instructtext2 = QString("Click screen to start");
              painter.translate(QPoint(width()/2, height()/2));
              int textwidth = status.width(instructtext);
              painter.drawText(-textwidth/2,0,instructtext);
              painter.translate(QPoint(0, 30));
              textwidth = status.width(instructtext2);
              painter.drawText(-textwidth/2,0,instructtext2);
          }
       }
	}
}

//player controls, movements and misc
void game::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A: //move left
      {
    playerobj->moveleft();
    break;
      }
    case Qt::Key_W: //move up
      {
    playerobj->moveup();
	break;
      }
    case Qt::Key_D: //move right
      {
    playerobj->moveright();
	break;
      }
    case Qt::Key_S: //move down
      {
    playerobj->movedown();
	break;
      }
    case Qt::Key_Space: //skip level
      {
        changelevel();
    break;
      }
    case Qt::Key_Escape: //exit program
      {
	qApp->exit();
	break;
      }
    }
}

//mouse event to attack
void game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (gamestarted) //attack
        {
            if (!playerswing)
            {
                QSound::play("sound/sword_swing.wav");
                playerobj->attack(event->x(), event->y());
                playerswing = true;
                QTimer::singleShot(timerswing, this, SLOT(PlayerSwingTimeOut()));
            }
        }
        else
        {
            gamestart();
            repaint();
            transitioning = false;
        }
    }
}

//timer event to allow movement/AI of all entities
void game::timerEvent(QTimerEvent *timerId)
{
  if (gamestarted == true)
  {
      for (int i = 0; i < enemy.size(); i++)
      {
          bool isattacking = false;
          character *obj = enemy.at(i);
          if (obj->getType() == "magicfirerebound")
              isattacking = obj->AI(enemy[0]); //change target of magic fire to lich king after hit
          else
              isattacking = obj->AI(playerobj);
          if (isattacking)
          {
              QString type = enemy[i]->getType();
              if (type == "archer")
                  fire_projectile(enemy[i]->getRect(),"archer");
              if (type == "exploder")
              {
                  fire_projectile(enemy[i]->getRect(),"exploder");
                  enemy[i]->reset();
              }
              if (type == "dragon")
                  fire_projectile(enemy[i]->getRect(),"dragon");
              if (type == "lichking")
                  fire_projectile(enemy[i]->getRect(),"lichking");
          }
      }
      for (int i = 0; i < bullet.size() ; i++)
      {
          projectile *obj = bullet.at(i);
          obj->move();
      }
  }
  if (level == 1 && killsleft == 0 && transitioning == false)
      changelevel();
  checkcollision();
  repaint();
}

//temporary invincibility and bump after player damaged
void game::player_hit(QRect enemy)
{
    if (lives != 0)
    {
        if (!was_hit)
        {
            QSound::play("sound/human_hurt.wav");
          lives--;
          was_hit = true;
          QTimer::singleShot(timerimmune, this, SLOT(PlayerImmuneTimeOut()));
        }
        if (playerobj->getRect().x() > enemy.x())
            playerobj->moveright();
        else
            playerobj->moveleft();
        if (playerobj->getRect().y() > enemy.y())
            playerobj->movedown();
        else
            playerobj->moveup();
    }
    else{
        QSound::play("sound/human_death.wav");
      gamestop();
    }
 }

void game::gamestart() //game start
{
  if (gamestarted == false)
    {
      //add characters for level 1
      if (level == 1)
      {
          for (int i = 0; i < 6; i++){
              enemy.append(new pirate(this));
              killsleft++;
          }
          for (int i = 0; i < 3; i++){
              enemy.append(new archer(this));
              killsleft++;
          }
          for (int i = 0; i < 6; i++)
              obstacle.append(new tree(this));
          //reset characters
          for (int i = 0; i < enemy.size(); i++)
          {
              character *obj = enemy.at(i);
              obj->reset();
          }
          for (int i = 0; i < obstacle.size(); i++)
          {
              character *obj = obstacle.at(i);
              obj->reset();
          }
      }
      if (level == 2)
      {
          enemy.append(new dragon(this));
          for (int i = 0; i < 3; i++)
              enemy.append(new sprite(this));
          for (int i = 0; i < 6; i++)
              obstacle.append(new lava(this));
          //reset characters
          for (int i = 0; i < enemy.size(); i++)
          {
              character *obj = enemy.at(i);
              obj->reset();
          }
          for (int i = 0; i < obstacle.size(); i++)
          {
              character *obj = obstacle.at(i);
              obj->reset();
          }
      }
      if (level == 3)
      {
          enemy.append(new lichking(this));
          //reset characters
          for (int i = 0; i < enemy.size(); i++)
          {
              character *obj = enemy.at(i);
              obj->reset();
          }
          for (int i = 0; i < obstacle.size(); i++)
          {
              character *obj = obstacle.at(i);
              obj->reset();
          }
      }
    }
  transitioning = false;
  playerobj->reset();
  killTimer(timerId);
  timerId = startTimer(10);
  gameover = false;
  gamestarted = true;
  was_hit = true;
  QTimer::singleShot(timerimmune, this, SLOT(PlayerImmuneTimeOut()));
}

void game::gamestop() //game stop
{
  clear_vectors();
  killTimer(timerId);
  lives = 3;
  score = 0;
  killsleft = 0;
  gameover = true;
  gamestarted = false;
}

//victory
void game::victory(){
    QSound::play("sound/fanfare.wav");
    background.load("images/level1.png");
    killsleft = 0;
    lives = 3;
    level = 1;
    gameover = true;
    gamestarted = false;
}

//clean out all of the vectors containing all characters/projectiles/obstacles
void game::clear_vectors()
{
    while (!enemy.isEmpty())
        delete enemy.takeFirst();
    while (!obstacle.isEmpty())
        delete obstacle.takeFirst();
    while (!bullet.isEmpty())
        delete bullet.takeFirst();

}

//enemy fired projectiles caller
void game::fire_projectile(QRect shooter, QString type)
{
    if (type == "archer")
    {
        QSound::play("sound/bow_shoot.wav");
        QString filename = "images/arrow_up.png";
        if (playerobj->getRect().x() < shooter.x()-shooter.height()*2) //shot left
            filename = "images/arrow_left.png";
        else if (playerobj->getRect().x() > shooter.x()+shooter.height()*2) //shot right
            filename = "images/arrow_right.png";
        if (playerobj->getRect().y() < shooter.y()-shooter.width()*2) //shot up
            filename = "images/arrow_up.png";
        else if (playerobj->getRect().y() > shooter.y()+shooter.width()*2) //shot down
            filename = "images/arrow_down.png";
        bullet.append(new arrow(filename, shooter, playerobj->getRect()));
    }
    if (type == "exploder")
    {
        QSound::play("sound/explode.wav");
        QString filename = "images/fireball_NE.png";
        bullet.append(new fireball(filename, shooter, -45)); //NE shot
        filename = "images/fireball_NW.png";
        bullet.append(new fireball(filename, shooter, -135)); //NW shot
        filename = "images/fireball_SE.png";
        bullet.append(new fireball(filename, shooter, 45)); //SE shot
        filename = "images/fireball_SW.png";
        bullet.append(new fireball(filename, shooter, 135)); //SW shot
    }
    if (type == "dragon")
    {
        QSound::play("sound/dragon_roar.wav");
        QString filename = "images/dragonfire.png";
        bullet.append(new dragonfire(filename, shooter, playerobj->getRect()));
    }
    if (type == "lichking")
    {
        if (!minions){
            QSound::play("sound/magic_fire.wav");
            enemy.append(new magicfire(this, shooter));
        }
        else
            for (int i = 0; i < 6; i++)
            {
                QSound::play("sound/lich_king_laugh.wav");
                enemy.append(new skeleton(this, shooter));
            }
        minions = !minions;
    }
}

//change level after conditions are met
void game::changelevel()
{
    gamestarted = false;
    if (level == 1 && transitioning == false){
        background.load("images/level2.png");
        level = 2;
        transitioning = true;
        clear_vectors();
    }
    if (level == 2 && transitioning == false){
        background.load("images/level3.png");
        level = 3;
        transitioning = true;
        clear_vectors();
    }
    if (level == 3 && transitioning == false){
        level = 4;
        transitioning = true;
        clear_vectors();
        victory();
        return;
    }
    killsleft = 0;
    gamestart();
}

void game::checkcollision() //collision check
{
  //player intersects an obstacle it will be hindered accordingly
  for (int i = 0; i < obstacle.size(); i++)
  {
      QString type = obstacle[i]->getType();  //gets obstacle type
      //player intersects solid object they will be pushed away
      if (type == "solid")
      {
          if ((playerobj->getRect()).intersects(obstacle[i]->getRect()))
          {
              if (playerobj->getRect().x() > obstacle[i]->getRect().x())
                  playerobj->moveright();
              else
                  playerobj->moveleft();
              if (playerobj->getRect().y() > obstacle[i]->getRect().y())
                  playerobj->movedown();
              else
                  playerobj->moveup();
          }
      }
      if (type == "lava")
      {
          if ((playerobj->getRect()).intersects(obstacle[i]->getRect()))
          {
              if (!was_hit)
                  player_hit(obstacle[i]->getRect());
              playerobj->reset();
              break;
          }
      }
  }
  //collisions for projectiles
  for (int i = 0; i < bullet.size(); i++)
  {
      if ((bullet[i]->getRect()).intersects(playerobj->getRect()))
      {
          player_hit(bullet[i]->getRect());
          if (!gameover)
          {
            delete bullet.takeAt(i);
          }
          break;
      }
      if ((bullet[i]->getRect().x()< 0) || (bullet[i]->getRect().x() > 400) || (bullet[i]->getRect().y()< 20) || (bullet[i]->getRect().y() > 420))
      {
          delete bullet.takeAt(i);
          break;
      }
      for (int j = 0; j < obstacle.size(); j++)
      {
          QString type = obstacle[j]->getType();  //gets obstacle type
          if (type == "solid")
          {
              if ((bullet[i]->getRect()).intersects(obstacle[j]->getRect()))
              {
                  delete bullet.takeAt(i);
                  break;
              }
          }
      }
  }
  //collisions for other characters
  for (int i = 0; i < enemy.size(); i++)
  {
      QString enemytype = enemy[i]->getType();
      //special damage conditions for lich king
      if (enemytype == "lichking")
      {
          for (int j = 0; j < enemy.size(); j++)
          {
              if ((enemy[i]->getRect()).intersects(enemy[j]->getRect()))
              {
                  character *lich = enemy[i];
                  character *magic = enemy[j];
                  if (magic->getType() == "magicfirerebound")
                  {
                      int life = lich->getLives();
                      if (life == 1)
                      {
                          score += 10;
                          killsleft--;
                          changelevel();
                          return;
                      }
                      else if (life > 1){
                          lich->damaged(magic);
                          QSound::play("sound/lich_king_hurt.wav");
                          delete enemy.takeAt(j);
                          break;
                      }
                  }
              }
          }
      }
      //remove a life from enemy if player hits it, kill it when its out of lives
      if ((enemy[i]->getRect()).intersects(playerobj->getAttackRect()))
      {
          int life = enemy[i]->getLives();
          if (life == 1)
          {
              if (enemytype != "lichking")
              {
                killsleft--;
                if (enemytype == "dragon"){
                    score += 5;
                    changelevel();
                    break;
                }
                score++;
                delete enemy.takeAt(i);
                break;
              }
          }
          else {
              if (enemytype == "lichking"){ //player can't directly harm the lich king
                player_hit(enemy[i]->getRect());
                break;
              }
              else{
                  QSound::play("sound/sword_hit.wav");
                enemy[i]->damaged(playerobj);
              }
          }

      }
      //enemy hits player it lose a life and is bumped away
      if ((playerobj->getRect()).intersects(enemy[i]->getRect()))
        {
          if (lives > 0){
            player_hit(enemy[i]->getRect());
            if (enemy[i]->getType() == "magicfire")
                delete enemy.takeAt(i);
          }
          else{
            player_hit(enemy[i]->getRect());
            return;
          }
        }
      //enemy hits an obstacle they will be hindered appropriately
      for (int j = 0; j < obstacle.size(); j++)
      {
          QString type = obstacle[j]->getType();  //gets obstacle type
          //enemy intersects solid object they will be pushed away
          if (type == "solid")
          {
              if ((enemy[i]->getRect()).intersects(obstacle[j]->getRect()))
              {
                  if (enemy[i]->getRect().x() > obstacle[j]->getRect().x())
                      enemy[i]->moveright();
                  else
                      enemy[i]->moveleft();
                  if (enemy[i]->getRect().y() > obstacle[j]->getRect().y())
                      enemy[i]->movedown();
                  else
                      enemy[i]->moveup();
              }
          }
      }
  }  
}

//timer for player swing
void game::PlayerSwingTimeOut(void)
{
    playerswing = false;
    playerobj->resetattack();
}

//timer for player invincibility
void game::PlayerImmuneTimeOut(void)
{
    was_hit = false;
    blink = false;
}

int main(int argc, char*argv[])
{
  QApplication app(argc, argv);
  int x,y;

  game window;
  window.setWindowTitle("HW 5 - Game");
  window.show();

  QDesktopWidget *desktop = QApplication::desktop();

  x = (desktop->width()-400)/2;
  y = (desktop->height()-420)/2;
  window.setGeometry(x,y,400,420);//set window size and initial placement
  window.setFixedSize(400,420);//prevents resizing of window

  return app.exec();
}

#include "sprite.h"

using namespace std;

sprite::sprite(QWidget *parent): character("images/sprite.png", parent,1)
{
    move_increment = 3;
    type = "exploder";
}

sprite::~sprite()
{
}

void sprite::moveleft()
{
    int left = rect.x() - move_increment;
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void sprite::moveup()
{
    int up = rect.y() - move_increment;
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void sprite::moveright()
{
    int right = rect.x() + move_increment;
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void sprite::movedown()
{
    int down = rect.y() + move_increment;
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

void sprite::reset()
{
  int randx = rand() % 380;
  int randy = rand() % 380 +20;
  rect.moveTo(randx,randy); //move to a random part of the playing field
}

bool sprite::AI(character *player)
{
    int playerx = player->getRect().x();
    int playery = player->getRect().y();
    int x = this->getRect().x();
    int y = this->getRect().y();
    int randommove = rand() % 8;
    switch (randommove)
      {
      case 0: //move left
        {
      this->moveleft();
      break;
        }
      case 1: //move left-up
        {
      this->moveleft();
      this->moveup();
      break;
        }
      case 2: //move up
        {
      this->moveup();
      break;
        }
      case 3: //move right-up
        {
      this->moveright();
      this->moveup();
      break;
        }
      case 4: //move right
        {
        this->moveright();
      break;
        }
      case 5: //move right-down
        {
      this->moveright();
      this->movedown();
      break;
        }
      case 6: //move down
        {
      this->movedown();
      break;
        }
      case 7: //move left-down
        {
      this->moveleft();
      this->movedown();
      break;
        }
      }
    if (playerx < x+80 && playerx  > x-80 && playery > y-80 && playery < y+80) //check to see if player is close to runner
    {
        return true;
    }
return false;
}

void sprite::damaged(character *enemy){
    if (!invulnerability)
    {
        lives--;
        invulnerability = true;
    }
    int playerx = enemy->getRect().x();
    int playery = enemy->getRect().y();
    int x = this->getRect().x();
    int y = this->getRect().y();
    if (playerx < x) //move right if player is to left
    {
        this->moveright();
    }
    if (playerx > x) //move left if player is to right
    {
        this->moveleft();
    }
    if (playery > y) //move up if player is below
    {
        this->moveup();
    }
    if (playery < y) //move down if player is above
    {
        this->movedown();
    }
    QTimer::singleShot(500, this, SLOT(Invulnerable()));
}

void sprite::Invulnerable(void)
{
    invulnerability = false;
}


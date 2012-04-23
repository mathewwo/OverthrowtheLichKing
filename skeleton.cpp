#include "skeleton.h"

using namespace std;

skeleton::skeleton(QWidget *parent, QRect origin): character("images/skeleton.png", parent, 3)
{
    move_increment = 1;
    oncooldown = true;
    knockback = false;
    invulnerability = false;
    rect.moveTo(origin.x()+(rand()%100+1), origin.y()+(rand()%100+1));
    type = "archer";

    QTimer::singleShot(1000, this, SLOT(TimeOut()));
}

skeleton::~skeleton()
{
}

void skeleton::moveleft()
{
    int left = rect.x() - move_increment;
    if (knockback){
        left = rect.x() - move_increment*30;
        knockback = false;
    }
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void skeleton::moveup()
{
    int up = rect.y() - move_increment;
    if (knockback){
        up = rect.y() - move_increment*30;
        knockback = false;
    }
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void skeleton::moveright()
{
    int right = rect.x() + move_increment;
    if (knockback){
        right = rect.x() + move_increment*30;
        knockback = false;
    }
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void skeleton::movedown()
{
    int down = rect.y() + move_increment;
    if (knockback){
        down = rect.y() + move_increment*30;
        knockback = false;
    }
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

bool skeleton::AI(character *playerobj)
{
    //move right if player is to right
    if (playerobj->getRect().x() > this->getRect().x())
      {
        this->moveright();
      }
    // move left if player is to left
    else if (playerobj->getRect().x() < this->getRect().x())
      {
        this->moveleft();
      }
    // move down if player is below
    if (playerobj->getRect().y() > this->getRect().y())
      {
        this->movedown();
      }
    // move up if player is above
    else if (playerobj->getRect().y() < this->getRect().y())
      {
        this->moveup();
      }
    if (!oncooldown){
        oncooldown = true;
        return true;
    }
    else
        return false;
}

void skeleton::damaged(character *enemy){
    //prevent chained hits til instant death
    if (!invulnerability)
    {
        lives--;
        invulnerability = true;
        knockback = true;
    }
    //knockback enemy away from player
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

void skeleton::TimeOut(void)
{
    oncooldown = false;
}

//can be hit again
void skeleton::Invulnerable(void)
{
    invulnerability = false;
}

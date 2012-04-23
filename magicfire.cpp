#include "magicfire.h"
#include <iostream>

using namespace std;

magicfire::magicfire(QWidget *parent, QRect origin): character("images/magicfire.png", parent, 0)
{
    move_increment = 3;
    type = "magicfire";
    rect.moveTo(origin.x(), origin.y());
}

magicfire::~magicfire()
{
}

void magicfire::moveleft()
{
    int left = rect.x() - move_increment;
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void magicfire::moveup()
{
    int up = rect.y() - move_increment;
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void magicfire::moveright()
{
    int right = rect.x() + move_increment;
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void magicfire::movedown()
{
    int down = rect.y() + move_increment;
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

void magicfire::reset()
{
  int randx = rand() % 380;
  int randy = rand() % 380 +20;
  rect.moveTo(randx,randy); //move to a random part of the playing field
}

bool magicfire::AI(character *playerobj)
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
    return false;
}

void magicfire::damaged(character *enemy){
    type = "magicfirerebound";
    std::cout << "bounce" << std::endl;
}

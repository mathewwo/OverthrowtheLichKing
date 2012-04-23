#include "player.h"

using namespace std;

player::player(QString filename, QWidget *parent): character(filename, parent,3)
{
    move_increment = 5;
    cooldown = false;
}

player::~player()
{
}

void player::moveleft()
{
    int left = rect.x() - move_increment;
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void player::moveup()
{
    int up = rect.y() - move_increment;
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void player::moveright()
{
    int right = rect.x() + move_increment;
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void player::movedown()
{
    int down = rect.y() + move_increment;
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

void player::attack(int x, int y)
{
    if (!cooldown)
    {
        int x_swing = 0;
        int y_swing = 0;
        if (x < rect.x()-rect.height()*2)
            dir = left;
        else if (x > rect.x()+rect.height()*2)
            dir = right;
        if (y < rect.y()-rect.width()*2)
            dir = up;
        else if (y > rect.y()+rect.width()*2)
            dir = down;
        switch(dir){
        case up:
            swing_image.load("images/swing_up.png");
            y_swing = -swing_image.height()/1.2;
            break;
        case down:
            swing_image.load("images/swing_down.png");
            y_swing = swing_image.height()/1.2;
            break;
        case left:
            swing_image.load("images/swing_left.png");
            x_swing = -swing_image.width()/1.2;
            break;
        case right:
            swing_image.load("images/swing_right.png");
            x_swing = swing_image.width()/1.2;
            break;
        }
        swing_rect = swing_image.rect();
        swing_rect.moveTo(rect.x()+x_swing, rect.y()+y_swing);
        cooldown = true;
    }
}

void player::resetattack()
{
    swing_rect.moveTo(0,0);
    cooldown = false;
}

void player::reset()
{
  int randx = rand() % 380;
  int randy = rand() % 380 +20;
  rect.moveTo(randx,randy); //move to a random part of the playing field
}

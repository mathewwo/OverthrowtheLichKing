#include "dragon.h"

using namespace std;

dragon::dragon(QWidget *parent): character("images/dragon.png", parent, 10)
{
    move_increment = 1;
    alertradius = 60;
    oncooldown = false;
    invulnerability = false;
    type = "dragon";

    cooldowntimer = new QTimer(this);
    cooldowntimer->start(4000);
    QObject::connect(cooldowntimer, SIGNAL(timeout()), this, SLOT(TimeOut()));
}

dragon::~dragon()
{
}

void dragon::moveleft()
{
    int left = rect.x() - move_increment;
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void dragon::moveup()
{
    int up = rect.y() - move_increment;
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void dragon::moveright()
{
    int right = rect.x() + move_increment;
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void dragon::movedown()
{
    int down = rect.y() + move_increment;
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

void dragon::reset()
{
  rect.moveTo(200,220); //move to a random part of the playing field
}

//move toward player at certain range
bool dragon::AI(character *playerobj)
{
    int playerx = playerobj->getRect().x();
    int playery = playerobj->getRect().y();
    int x = this->getRect().x();
    int y = this->getRect().y();
    if (playerx < x+alertradius && playerx  > x-alertradius && playery > y-alertradius && playery < y+alertradius) //check to see if player is close to runner
    {
        if (playerx < x)
        {
            this->moveleft();
        }
        if (playerx > x)
        {
            this->moveright();
        }
        if (playery > y)
        {
            this->movedown();
        }
        if (playery < y)
        {
            this->moveup();
        }
    }
    if (!oncooldown){
        oncooldown = true;
        return true;
    }
    else
        return false;
}

void dragon::damaged(character *enemy){
    if (!invulnerability)
    {
        lives--;
        invulnerability = true;
    }
    QTimer::singleShot(2000, this, SLOT(Invulnerable()));
}

void dragon::TimeOut(void)
{
    oncooldown = false;
}

void dragon::Invulnerable(void)
{
    invulnerability = false;
}

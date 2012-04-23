#include "archer.h"

using namespace std;

archer::archer(QWidget *parent): character("images/archer.png", parent, 1)
{
    move_increment = 1;
    alertradius = 60;
    oncooldown = false;
    invulnerability = false;
    type = "archer";

    cooldowntimer = new QTimer(this);
    cooldowntimer->start(3000);
    QObject::connect(cooldowntimer, SIGNAL(timeout()), this, SLOT(TimeOut()));
}

archer::~archer()
{
}

void archer::moveleft()
{
    int left = rect.x() - move_increment;
    if (rect.left() >= 0) //keep moving until hit edge of screen
        rect.moveTo(left, rect.top());
    if (rect.left() < 0) //screen wrap after hitting edge
        rect.moveTo(400-rect.width(), rect.top());
}

void archer::moveup()
{
    int up = rect.y() - move_increment;
    if (rect.top() >= 20) //keep moving until hit score/lives hud
        rect.moveTo(rect.left(), up);
    if (rect.top() < 20) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 420-rect.height());
}

void archer::moveright()
{
    int right = rect.x() + move_increment;
    if (rect.right() <= 400) //keep moving until hit edge of screen
        rect.moveTo(right, rect.top());
    if (rect.right() > 400) //screen wrap after hitting edge
        rect.moveTo(0, rect.top());
}

void archer::movedown()
{
    int down = rect.y() + move_increment;
    if (rect.bottom() <= 420) //keep moving until hit edge of screen
        rect.moveTo(rect.left(), down);
    if (rect.bottom() > 420) //screen wrap after hitting edge
        rect.moveTo(rect.left(), 20);
}

void archer::reset()
{
  int randx = rand() % 380;
  int randy = rand() % 380 +20;
  rect.moveTo(randx,randy); //move to a random part of the playing field
}

//run from player when within alert radius which decreases when chased to simulate fatigue
bool archer::AI(character *playerobj)
{
    int playerx = playerobj->getRect().x();
    int playery = playerobj->getRect().y();
    int x = this->getRect().x();
    int y = this->getRect().y();
    if (playerx < x+alertradius && playerx  > x-alertradius && playery > y-alertradius && playery < y+alertradius) //check to see if player is close to runner
    {
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
        if (!oncooldown)
            oncooldown = true;  //prevents firing when chased
        alertradius -= 0.5; //simulate fatigue
    }
    if (!oncooldown){
        oncooldown = true;
        return true;
    }
    else
        return false;
}

void archer::damaged(character *enemy){
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

void archer::TimeOut(void)
{
    oncooldown = false;
    alertradius = 40;  //resets alert radius
}

void archer::Invulnerable(void)
{
    invulnerability = false;
}

#include "lichking.h"

using namespace std;

lichking::lichking(QWidget *parent): character("images/lichking.png", parent, 3)
{
    oncooldown = false;
    type = "lichking";

    cooldowntimer = new QTimer(this);
    cooldowntimer->start(5000);
    QObject::connect(cooldowntimer, SIGNAL(timeout()), this, SLOT(TimeOut()));
}

lichking::~lichking()
{
}

void lichking::reset()
{
  int randx = rand() % 300;
  int randy = rand() % 300 +20;
  rect.moveTo(randx,randy); //move to a random part of the playing field
}

bool lichking::AI(character *playerobj)
{
    if (!oncooldown){
        oncooldown = true;
        return true;
    }
    else
        return false;
}

void lichking::damaged(character *enemy){
    lives--;
    this->reset();
}

void lichking::TimeOut(void)
{
    oncooldown = false;
}

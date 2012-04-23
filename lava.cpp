#include "lava.h"

using namespace std;

lava::lava(QWidget *parent): character("images/lava.png", parent, 0)
{
    type = "lava";
}

lava::~lava()
{
}

void lava::reset()
{
    int randx = rand() % 360;
    int randy = rand() % 360 +20;
    rect.moveTo(randx,randy); //move to a random part of the playing field
}

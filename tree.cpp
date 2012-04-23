#include "tree.h"

using namespace std;

tree::tree(QWidget *parent): character("images/tree.png", parent, 0)
{
    type = "solid";
}

tree::~tree()
{
}

void tree::reset()
{
    int randx = rand() % 360;
    int randy = rand() % 360 +20;
    rect.moveTo(randx,randy); //move to a random part of the playing field
}

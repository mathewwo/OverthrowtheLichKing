#include <iostream>
#include "character.h"

character::character(QString filename, QWidget *parent, int life) : QWidget(parent)
{
    lives = life;
    image.load(filename);
    rect = image.rect();
}

character::~character()
{
}

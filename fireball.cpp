#include "fireball.h"
#include <iostream>

using namespace std;

fireball::fireball(QString filename, QRect shooter, float angle): projectile(filename)
{
    move_increment = 2;
    origin = shooter;
    shootangle = angle * (3.14159265 / 180);
    rect.moveTo(origin.x(),origin.y());

}

fireball::~fireball()
{
}

void fireball::move()
{
    float velocity = move_increment;
    float radians = shootangle; //* 3.14159265 / 180;

    float velx = velocity * cos(radians);
    float vely = velocity * sin(radians);

    float x = (rect.x()) + velx;
    float y = (rect.y()) + vely;

    rect.moveTo(x,y);
}


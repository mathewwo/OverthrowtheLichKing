#include "dragonfire.h"

using namespace std;

dragonfire::dragonfire(QString filename, QRect shooter, QRect player): projectile(filename)
{
    move_increment = 2;
    origin = shooter;
    target = player;
    rect.moveTo(origin.x(),origin.y());
    shootangle = atan2((float)target.y() - (float)origin.y(), (float)target.x() - (float)origin.x());
}

dragonfire::~dragonfire()
{
}

void dragonfire::move()
{
    float velocity = move_increment;
    float radians = shootangle; //* 3.14159265 / 180;

    float velx = velocity * cos(radians);
    float vely = velocity * sin(radians);

    float x = (rect.x()) + velx;
    float y = (rect.y()) + vely;

    rect.moveTo(x,y);
}

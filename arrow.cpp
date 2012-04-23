#include "arrow.h"

using namespace std;

arrow::arrow(QString filename, QRect shooter, QRect player): projectile(filename)
{
    move_increment = 5;
    origin = shooter;
    target = player;
    rect.moveTo(origin.x(),origin.y());
    shootangle = atan2((float)target.y() - (float)origin.y(), (float)target.x() - (float)origin.x());
}

arrow::~arrow()
{
}

void arrow::move()
{
    float velocity = move_increment;
    float radians = shootangle; //* 3.14159265 / 180;

    float velx = velocity * cos(radians);
    float vely = velocity * sin(radians);

    float x = (rect.x()) + velx;
    float y = (rect.y()) + vely;

    rect.moveTo(x,y);
}

#ifndef FIREBALL_H
#define FIREBALL_H

#include "projectile.h"

class fireball: public projectile
{
    private:
        int move_increment;
        float shootangle;
        QRect origin;

    public:
        fireball(QString filename, QRect shooter, float angle);
        ~fireball();

        void move();
};

#endif // FIREBALL_H

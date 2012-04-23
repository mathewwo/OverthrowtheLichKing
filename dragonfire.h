#ifndef DRAGONFIRE_H
#define DRAGONFIRE_H

#include "projectile.h"

class dragonfire: public projectile
{
    private:
        int move_increment;
        float shootangle;
        QRect origin, target;

    public:
        dragonfire(QString filename, QRect shooter, QRect player);
        ~dragonfire();

        void move();
};

#endif // DRAGONFIRE_H

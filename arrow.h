#ifndef ARROW_H
#define ARROW_H

#include "projectile.h"

class arrow: public projectile
{
    private:
        int move_increment;
        float shootangle;
        QRect origin, target;

    public:
        arrow(QString filename, QRect shooter, QRect player);
        ~arrow();

        void move();
};

#endif // ARROW_H

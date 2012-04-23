#ifndef LAVA_H
#define LAVA_H

#include "character.h"

class lava : public character
{
    private:
        QString type;
    public:
        lava(QWidget *parent);
        ~lava();

        void reset(); //reset object
        QString getType(){return type;}
};

#endif // LAVA_H

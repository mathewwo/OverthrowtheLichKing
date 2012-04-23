#ifndef MAGICFIRE_H
#define MAGICFIRE_H

#include "character.h"

class magicfire : public character
{
    Q_OBJECT
    private:
        int move_increment;
        QString type;
        character *target;

    public:
        magicfire(QWidget *parent, QRect origin);
        ~magicfire();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        QString getType(){return type;}
        void damaged(character *enemy);
        void reset();//reset object
        bool AI(character *target);
};


#endif // MAGICFIRE_H

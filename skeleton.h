#ifndef SKELETON_H
#define SKELETON_H

#include "character.h"

class skeleton : public character
{
    Q_OBJECT
    private:
        int move_increment;
        bool invulnerability, knockback, oncooldown;
        QString type;

    public:
        skeleton(QWidget *parent, QRect origin);
        ~skeleton();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        QString getType(){return type;}
        void damaged(character *enemy);
        bool AI(character *target);

    private slots:
        void TimeOut(void);
        void Invulnerable(void);
};

#endif


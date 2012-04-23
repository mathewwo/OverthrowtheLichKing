#ifndef pirate_H
#define pirate_H

#include "character.h"

class pirate : public character
{
    Q_OBJECT
    private:
        int move_increment;
        bool invulnerability, knockback;

    public:
        pirate(QWidget *parent);
        ~pirate();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        void damaged(character *enemy);
        void reset();//reset object
        bool AI(character *target);

    private slots:
        void Invulnerable(void);
};

#endif

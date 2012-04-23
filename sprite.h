#ifndef sprite_H
#define sprite_H

#include "character.h"

class sprite: public character
{
    Q_OBJECT
    private:
        int move_increment;
        bool invulnerability;
        QString type;

    public:
        sprite(QWidget *parent);
        ~sprite();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        void damaged(character *enemy);
        QString getType(){return type;}
        void reset();//reset object
        bool AI(character *player);

        private slots:
            void Invulnerable(void);
};

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class player : public character
{
    private:
        enum player_dir{
            up,
            down,
            left,
            right
        };
        player_dir dir;
        int move_increment;
        bool cooldown;
        QRect swing_rect;
        QImage swing_image;

    public:
        player(QString filename, QWidget *parent);
        ~player();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        void attack(int x, int y);
        void resetattack();
        void reset();//reset object
        virtual QRect getAttackRect(){return swing_rect;}
        virtual QImage &getAttackImage(){return swing_image;}
};

#endif // PLAYER_H

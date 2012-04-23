#ifndef archer_H
#define archer_H

#include "character.h"

class archer : public character
{
    Q_OBJECT
    private:
        int move_increment;
        float alertradius;
        bool oncooldown, invulnerability;
        QString type;
        QTimer* cooldowntimer;

    public:
        archer(QWidget *parent);
        ~archer();

        //controls
        void moveleft();
        void moveup();
        void moveright();
        void movedown();

        QString getType(){return type;}
        void damaged(character *enemy);
        void reset();//reset object
        bool AI(character *playerobj);

    private slots:
        void TimeOut(void);
        void Invulnerable(void);
};

#endif

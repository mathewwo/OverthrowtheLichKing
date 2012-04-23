#ifndef DRAGON_H
#define DRAGON_H

#include "character.h"

class dragon : public character
{
    Q_OBJECT
    private:
        int move_increment, alertradius;
        bool oncooldown, invulnerability;
        QString type;
        QTimer* cooldowntimer;

    public:
        dragon(QWidget *parent);
        ~dragon();

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

#endif // DRAGON_H

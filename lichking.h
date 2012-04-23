#ifndef LICHKING_H
#define LICHKING_H

#include "character.h"

class lichking : public character
{
    Q_OBJECT
    private:
        bool oncooldown;
        QString type;
        QTimer* cooldowntimer;

    public:
        lichking(QWidget *parent);
        ~lichking();

        QString getType(){return type;}
        void damaged(character *enemy);
        void reset();//reset object
        bool AI(character *playerobj);

    private slots:
        void TimeOut(void);
};

#endif // LICHKING_H

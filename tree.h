#ifndef tree_H
#define tree_H

#include "character.h"

class tree : public character
{
    private:
        QString type;
    public:
        tree(QWidget *parent);
        ~tree();

        void reset(); //reset object
        QString getType(){return type;}
};

#endif

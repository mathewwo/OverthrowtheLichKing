#include <iostream>
#include "projectile.h"

projectile::projectile(QString filename)
{
    image.load(filename);
    rect = image.rect();
}

projectile::~projectile()
{
}

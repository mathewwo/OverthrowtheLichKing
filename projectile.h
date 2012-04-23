#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QImage>
#include <QRect>
#include <cmath>

class projectile
{
 protected:
    QImage image;
    QRect rect;

 public:
  projectile(QString filename);
  virtual ~projectile();

  virtual void move(){}
  QRect getRect(){return rect;}
  QImage &getImage(){return image;}
};

#endif // PROJECTILE_H

#ifndef character_H
#define character_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QRect>

class character : public QWidget
{
 protected:
    int lives;
    QImage image;
    QRect rect;

 public:
  character(QString filename, QWidget *parent, int life);
  virtual ~character();

  //controls
  virtual void moveleft(){}
  virtual void moveup(){}
  virtual void moveright(){}
  virtual void movedown(){}
  virtual bool AI(character*){return false;}

  virtual void attack(int x, int y){}
  virtual void resetattack(){}
  virtual void damaged(character*){}
  virtual void reset(){}//reset object
  virtual QString getType(){return "";}
  QRect getRect(){return rect;}
  QImage &getImage(){return image;}
  int getLives(){return lives;}
  virtual QRect getAttackRect(){return rect;}
  virtual QImage &getAttackImage(){return image;}
};

#endif

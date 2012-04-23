#ifndef hw5_H
#define hw5_H

#include <QWidget>
#include <QSound>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QList>
#include "character.h"
#include "player.h"
#include "pirate.h"
#include "sprite.h"
#include "archer.h"
#include "tree.h"
#include "arrow.h"
#include "fireball.h"
#include "lava.h"
#include "dragon.h"
#include "dragonfire.h"
#include "lichking.h"
#include "magicfire.h"
#include "skeleton.h"

class game : public QWidget
{
 Q_OBJECT
 private:
  int lives, score, timerId, timerimmune, timerswing, level, killsleft;
  QList<character*> enemy;
  QList<projectile*> bullet;
  QList<character*> obstacle;
  character *playerobj;
  QImage background;
  bool minions;
  bool gameover;
  bool gamestarted;
  bool playerswing;
  bool was_hit;
  bool blink;
  bool transitioning;

 public:
  game(QWidget *parent = 0);
  ~game();

  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  
  void timerEvent(QTimerEvent *timerId);
  void player_hit(QRect enemy);
  void clear_vectors();
  void fire_projectile(QRect shooter, QString type);
  void gamestart();
  void gamestop();
  void victory();
  void changelevel();
  void checkcollision();

 private slots:
  void PlayerSwingTimeOut(void);
  void PlayerImmuneTimeOut(void);

};

#endif

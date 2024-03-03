#ifndef SPACEBULLET_H
#define SPACEBULLET_H

#include "Bullet.h"
#include <QGraphicsItem>
#include <QObject>

class SpaceBullet: public Bullet{
    Q_OBJECT
public:
    int speedBoost = 0;
    SpaceBullet(QGraphicsItem* parent = 0);
public slots:
    virtual void move();

};

#endif // SPACEBULLET_H

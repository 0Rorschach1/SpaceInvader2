#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Alien.h"
#include "spaceship.h"

#include <QObject>

class obstacle : public Alien{
    Q_OBJECT
public:

    obstacle(QGraphicsItem* parent3  , int xx , int yy);
    virtual ~obstacle();
    QTimer* timer3();

    void updateHealth3(int h);

private:
    virtual bool checkCollisions();
    void startTimer3(int t);
    int health3_;

    QTimer* timer3_;
    QTimer* rate3;
public slots:
    virtual void move();

};

#endif

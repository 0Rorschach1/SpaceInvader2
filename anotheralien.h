#ifndef ANOTHERALIEN_H
#define ANOTHERALIEN_H

#include "Alien.h"
#include "spaceship.h"
#include <QObject>

class AnotherAlien: public Alien {
    Q_OBJECT
public:
    int speedBoost2 ;
    QTimer *speedBoostTimer2;
    AnotherAlien(QGraphicsItem* parent2 = 0);
    virtual ~AnotherAlien();
    QTimer* timer2();
    int health2();
    int reset2();
    void updateHealth2(int h);

private:
    virtual bool checkCollisions();
    void startTimer2(int t);
    int health2_;

    QTimer* timer2_;
    QTimer* rate2;
public slots:
    virtual void move();
};

#endif // AnotherAlien_H

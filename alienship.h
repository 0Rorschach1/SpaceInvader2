#ifndef ALIENSHIP_H
#define ALIENSHIP_H

#include "Alien.h"
#include "spaceship.h"
#include <QObject>

class AlienShip: public Alien {
    Q_OBJECT
public:
    int speedBoost ;
    QTimer *speedBoostTimer;
    AlienShip(QGraphicsItem* parent = 0);
    virtual ~AlienShip();
    QTimer* timer();
    int health();
    int reset();
    void updateHealth(int h);

private:
    virtual bool checkCollisions();
    void startTimer(int t);
    int health_;

    QTimer* timer_;
    QTimer* rate;
public slots:
    virtual void move();
};

#endif // ALIENSHIP_H

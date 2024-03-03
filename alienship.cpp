#include "AlienShip.h"
#include <QDebug>
#include <QPixmap>
#include "Game.h"
#include <typeinfo>
#include "SpaceBullet.h"
#include "AlienBullet.h"

extern Game* game;

AlienShip::AlienShip(QGraphicsItem* parent): Alien(parent)
{

    setPic(QPixmap(":/Resources/AlienShip.png"));
    setHeight(70);
    setWidth(70);
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
    setX(0);
    setY(60);

    health_ = 100;
    timer_ = new QTimer(this);
    timer_->setSingleShot(true);
    rate = new QTimer(this);
    rate->setSingleShot(true);
    startTimer(200000);



}

AlienShip::~AlienShip(){
    delete timer_;
    delete rate;
}

void AlienShip::startTimer(int t){
    timer_->start(t);
    getTimer()->start(100);
}

int AlienShip::health(){
    return health_;
}

void AlienShip::updateHealth(int h){
    health_ = h;
}
int AlienShip::reset(){
    if (game->getShip() != nullptr) {
        game->getShip()->speedBoost = 0;
    }
}

bool AlienShip::checkCollisions()
{
    QList<QGraphicsItem*> collided = collidingItems();
    for (int i = 0; i < collided.size(); ++i) {
        SpaceShip* spaceShip = dynamic_cast<SpaceShip*>(collided[i]);
        if (spaceShip != nullptr) {
            game->getBoard()->updateScore(game->getBoard()->score() - 10);
            delete this;
            return true;
        }

        SpaceBullet* spaceBullet = dynamic_cast<SpaceBullet*>(collided[i]);
        if (spaceBullet != nullptr) {
            spaceBullet->getTimer()->stop();
            delete spaceBullet;
            game->getBoard()->updateScore(game->getBoard()->score() + 3);
            speedBoostTimer = new QTimer(this);
            speedBoostTimer->start(7000);
            game->getShip()->speedBoost = 20;
            connect(speedBoostTimer, &QTimer::timeout, this, &AlienShip::reset);

            if (health() < 10) {
                delete this;
                return true;
            } else {
                health_ -= 10;
            }
        }
    }
    return false;
}


void AlienShip::move(){
    if(game->getShip()->health() <= 0){
        getTimer()->stop();
    }
    if(checkCollisions()) return;
    if(timer_->isActive()){
        if(!rate->isActive() && game->state() == game->State::ongoing){
            // create bullet and shoot.
            AlienBullet* b = new AlienBullet();
            b->setPos(x() + 5,y() + 13);
            scene()->addItem(b);
            rate->start(1000);
        }
        if(game->getShip()->x() < x()){
            setX(x() - 5);
        }
        else if(game->getShip()->x() > x()){
            setX(x() + 5);
        }
    }
    else{
        if(x() > -40){
            setX(x() - 10);
        }
        else{
            qDebug() << "object hidden.";
            getTimer()->stop();
        }
    }
}

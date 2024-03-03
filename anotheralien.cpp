#include "anotheralien.h"
#include <QDebug>
#include <QPixmap>
#include "Game.h"
#include <typeinfo>
#include "SpaceBullet.h"
#include "AlienBullet.h"


extern Game* game;

AnotherAlien::AnotherAlien(QGraphicsItem* parent2): Alien(parent2)
{
    // set graphics.
    setPic(QPixmap(":/Resources/AlienShip.png"));
    setHeight(70);
    setWidth(70);
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
    setX(300);
    setY(300);

    health2_ = 100;
    timer2_ = new QTimer(this);
    timer2_->setSingleShot(true);
    rate2 = new QTimer(this);
    rate2->setSingleShot(true);
    startTimer2(200000);



}

AnotherAlien::~AnotherAlien(){
    delete timer2_;
    delete rate2;
}

void AnotherAlien::startTimer2(int t){
    timer2_->start(t);
    getTimer()->start(100);
}

int AnotherAlien::health2(){
    return health2_;
}

void AnotherAlien::updateHealth2(int h){
    health2_ = h;
}
int AnotherAlien::reset2(){
    if (game->getShip() != nullptr) {
        game->getShip()->speedBoost = 0;
    }
}

bool AnotherAlien::checkCollisions()
{
    QList<QGraphicsItem*> collided2 = collidingItems();
    for (int i = 0; i < collided2.size(); ++i) {
        SpaceShip* spaceShip = dynamic_cast<SpaceShip*>(collided2[i]);
        if (spaceShip != nullptr) {
            game->getBoard()->updateScore(game->getBoard()->score() - 10);
            delete this;
            return true;
        }

        SpaceBullet* spaceBullet = dynamic_cast<SpaceBullet*>(collided2[i]);
        if (spaceBullet != nullptr) {
            spaceBullet->getTimer()->stop();
            delete spaceBullet;
            game->getBoard()->updateScore(game->getBoard()->score() + 3);
            speedBoostTimer2 = new QTimer(this);
            speedBoostTimer2->start(7000);
            game->getShip()->speedBoost = 20;
            connect(speedBoostTimer2, &QTimer::timeout, this, &AnotherAlien::reset2);

            if (health2() < 10) {
                delete this;
                return true;
            }
            else {
                health2_ -= 10;
            }
        }
    }
    return false;
}
bool f = 0;
void AnotherAlien::move(){
    if(game->getShip()->health() <= 0){

        getTimer()->stop();
    }
    if(checkCollisions()) return;
    if(timer2_->isActive()){
        if(!rate2->isActive() && game->state() == game->State::ongoing){
            // create bullet and shoot.
            AlienBullet* b = new AlienBullet();
            b->setPos(x() + 5,y() + 13);
            scene()->addItem(b);
            rate2->start(1000);
        }

        if(!f){
            setX(x()+10);
            if(x()>600) f = 1;
        }
        else{
            setX(x() -10);
            if(x() < 40) f = 0;
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

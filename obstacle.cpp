#include "obstacle.h"
#include <QDebug>
#include <QPixmap>
#include "Game.h"
#include <typeinfo>
#include "SpaceBullet.h"
#include "AlienBullet.h"

extern Game* game;

obstacle::obstacle(QGraphicsItem* parent3  , int xx , int yy) : Alien(parent3){

    setPic(QPixmap(":/Resources/omzBbel.png") );
    setHeight(120);
    setWidth(90);
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
    setX(xx);
    setY(yy);

    health3_ = 100;
    timer3_ = new QTimer(this);
    timer3_->setSingleShot(true);
    rate3 = new QTimer(this);
    rate3->setSingleShot(true);
    startTimer3(200);

}

obstacle::~obstacle(){
    delete timer3_;
    delete rate3;
}
void obstacle::startTimer3(int t){
    timer3_->start(t);
    getTimer()->start(100);
}



bool obstacle::checkCollisions()
{

    QList<QGraphicsItem*> collidedItems = collidingItems();


    for (int i = 0; i < collidedItems.size(); ++i) {

        SpaceBullet* spacebullet = dynamic_cast<SpaceBullet*>(collidedItems[i]);
        if (spacebullet != nullptr) {

            spacebullet->getTimer()->stop();
            //delete spacebullet;




        }



        AlienBullet* alienBullet = dynamic_cast<AlienBullet*>(collidedItems[i]);
        if (alienBullet != nullptr) {

            alienBullet->getTimer()->stop();



            delete alienBullet;


        }
    }



}
void obstacle::move(){


        if(checkCollisions()) return;



}




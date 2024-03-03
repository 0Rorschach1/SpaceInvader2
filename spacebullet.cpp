#include "spacebullet.h"
#include "game.h"

extern Game* game;

SpaceBullet::SpaceBullet(QGraphicsItem* parent): Bullet(parent)
{

    setPic(QPixmap(":/Resources/bullet.png"));
    setPic(getPic().scaled(QSize(30,30), Qt::KeepAspectRatio));

    setPixmap(getPic());
}

void SpaceBullet::move(){
    int baseSpeed = 10;
    int boostedSpeed = baseSpeed + game->getShip()->speedBoost;

    if( ((x() < (game->width() - 500) / 2) || x() > ((game->width() - 500) / 2) + 500) && y() > 0){
        if(y() > 0){
            setY(y() - boostedSpeed);
        }
        else{
            delete this;
        }
    }
    else{
        if(y() > 55){
            setY(y() - boostedSpeed);
        }
        else{
            delete this;
        }
    }
}

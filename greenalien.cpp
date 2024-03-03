#include "greenalien.h"
#include <QTimer>
#include <QDebug>
#include <typeinfo>
#include "spaceship.h"
#include "spacebullet.h"
#include "Game.h"
#include <QObject>
extern Game* game;

GreenAlien::GreenAlien(QGraphicsItem* parent) : Alien(parent)
{

    setPic(QPixmap(":/Resources/greenAlien.png"));
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
}

GreenAlien::GreenAlien(int x, int y) : Alien(x, y)
{

    setPic(QPixmap(":/Resources/greenAlien.png"));
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
}

GreenAlien::GreenAlien(int x, int y, Alien::Direction dX, Alien::Direction dY): Alien(x, y, dX, dY)
{

    setPic(QPixmap(":/Resources/greenAlien.png"));
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
}

GreenAlien::GreenAlien(int x, int y, Alien::Direction dX, Alien::Direction dY, int leftL, int upL, int rightL, int downL, int xLimit, int yLimit): Alien(x, y, dX, dY, leftL, upL, rightL, downL, xLimit, yLimit)
{

    setPic(QPixmap(":/Resources/greenAlien.png"));
    setPic(getPic().scaled(QSize(width(),height()), Qt::KeepAspectRatio));
    setPixmap(getPic());
}

GreenAlien::~GreenAlien(){
    game->delAlien(this);
}

bool GreenAlien::checkCollisions(){
    QList<QGraphicsItem *> collided = collidingItems();
    for(int i = 0; i < collided.size(); ++i){
        if(typeid((*collided[i])) == typeid(SpaceShip)){
            game->getBoard()->updateScore(game->getBoard()->score() - 1);
            (dynamic_cast<SpaceShip*> (collided[i]))->updateHealth(
                (dynamic_cast<SpaceShip*> (collided[i]))->health() - 10);
            game->updateCount(game->count() - 1);
            delete this;
            if(game->count() == 0){
                game->win();
            }
            return true;
        }
        else if(typeid((*collided[i])) == typeid(SpaceBullet)){
            (dynamic_cast<SpaceBullet*> (collided[i]))->getTimer()->stop();
            delete (dynamic_cast<SpaceBullet*> (collided[i]));
            game->getBoard()->updateScore(game->getBoard()->score() + 1);
            game->updateCount(game->count() - 1);
            delete this;
            if(game->count() == 0){
                qDebug() << "count is zero.";
                game->win();
            }
            return true;
        }


    }
    return false;
}


void GreenAlien::move(){
    if(checkCollisions() || (game->State::ongoing != game->state())) return;
    if(isGoingLeft()){

        if(x() > getXLim()){
            setX(x() - 5);
        }
        else{

            setXDirection(right);
            setXLim(getRightLim());
            if(y() < getYLim()){
                setY(y() + 20);

            }
            else{

                qDebug() << "Game is over.";
            }

        }
    }
    else{

        if(x() + 40 < getXLim()){
            setX(x() + 5);
        }
        else{

            setXDirection(left);
            setXLim(getLeftLim());
            if(y() < getYLim()){
                setY(y() + 20);
                //setRate(getRate() - 1);
            }
            else{


                qDebug() << "Game is over. y: " << y()  << "ylim: " << getYLim();
                game->lose();
            }

        }
    }
}

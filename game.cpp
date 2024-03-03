#include "game.h"
#include "bullet.h"
#include "scoreboard.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include "alienship.h"
#include "obstacle.h"
#include "anotheralien.h"


Game::Game() : QGraphicsView() {
    state_ = ongoing;
    const int FREE_SPACE = 15; //distance between 
    const int rows = 3;//number of colomuns and rows
    count_ = 0;

    setFixedSize(800, 600);
    scene = new QGraphicsScene(this);//creates a new graphic scene
    scene->setSceneRect(0, 0, 800, 600);//scene dimentions 
    setScene(scene);//set the scene using graphicview

    ship = new SpaceShip();
    ship->setPos((scene->width() / 2) - (ship->getWidth() / 2), scene->height() - (ship->getHeight() * 1));//spaceship position
    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();

    scene->addItem(ship);
    scoreB = new ScoreBoard();//scoreboard object

    aliens_ = new QVector<QVector<GreenAlien*>*>();//for removing

    int len = scene->width() / 40;//avalaible places for aliens
    int real_len = len - FREE_SPACE;
    int aliens_width = real_len * 40;
    int x_spacing = (scene->width() - aliens_width) / 2;
    int x_start = x_spacing;
    int x_end = aliens_width + x_spacing;

    qDebug() << "l: " << scene->width() << "start: " << x_start << ", end: " << x_end;
    for (int y = 0; y < rows; ++y) {
        aliens_->push_back(new QVector<GreenAlien*>());//creates a vector for each row of aliens
        for (int x = 0; x < real_len; ++x) {
            GreenAlien* alien = new GreenAlien((x * 40) + x_start, (45 * y) + 100);
            alien->setLeftLim(x * alien->width());
            alien->setRightLim(((x + (FREE_SPACE + 1)) * alien->width()));
            alien->setUpLim(800);
            alien->setDownLim(500);
            alien->setYDirection(Alien::Direction::down);
            alien->setXDirection(Alien::Direction::left);
            alien->start(100);
            aliens_->back()->push_back(alien);
            scene->addItem(alien);
            ++count_;
        }
    }

    AlienShip* alien = new AlienShip();
    AnotherAlien *alien2 = new AnotherAlien();
    obstacle *obs = new obstacle(nullptr , 550 , 380);
    obstacle *obs2 = new obstacle(nullptr , 100 , 380);
    scene->addItem(alien);
    scene->addItem(alien2);
    scene->addItem(obs);
    scene->addItem(obs2);

    scene->addItem(scoreB);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

ScoreBoard* Game::getBoard() {
    return scoreB;
}

SpaceShip* Game::getShip() {
    return ship;
}

int Game::count() {
    return count_;
}

QVector<GreenAlien*>* Game::aliens(int i) {
    return (*aliens_)[i];
}

void Game::updateCount(int c) {
    count_ = c;
}

Game::State Game::state() {
    return state_;
}

void Game::delAlien(GreenAlien* alien) {
    for (int y = 0, yEnd = aliens_->size(); y < yEnd; ++y) {
        for (int x = 0, xEnd = (*aliens_)[y]->size(); x < xEnd; ++x) {
            if ((*aliens_)[y]->operator[](x) == alien) {
                (*aliens_)[y]->remove(x);
                return;
            }
        }
    }
}

void Game::lose() {
    over(lost);
}

void Game::win() {
    over(won);
}

void Game::over(Game::State newState) {
    if (state() != ongoing) {
        qDebug() << "game already paused.";
        return;
    } else {
        state_ = newState;
    }



    for (int y = 0, yEnd = aliens_->size(); y < yEnd; ++y) {
        for (int x = 0, xEnd = (*aliens_)[y]->size(); x < xEnd; ++x) {
            (*aliens_)[y]->operator[](x)->getTimer()->stop();
            qDebug() << "timer stopped.";
        }
    }
    if (state() == won) {
        qDebug() << "you won.";
    } else {
        qDebug() << "Game over.";
    }
}

#include "scoreboard.h"
#include "game.h"
#include <QRectF>
#include <QDebug>

extern Game* game;

ScoreBoard::ScoreBoard()
{
    scoreTextItem_ = new QGraphicsTextItem(this);
    scoreTextItem_->setPos(0, 0);

    healthTextItem_ = new QGraphicsTextItem(this);
    healthTextItem_->setPos(0, 12);

    setRect(0, 0, 100, 100);
}

ScoreBoard::ScoreBoard(int s)
{
    scoreTextItem_ = new QGraphicsTextItem(this);
    scoreTextItem_->setPos(0, 0);
    scoreTextItem_->setPlainText("Score: " + QString::number(s));

    healthTextItem_ = new QGraphicsTextItem(this);
    healthTextItem_->setPos(0, 12);
    healthTextItem_->setPlainText("Health: " + QString::number(game->getShip()->health()));

    setRect(0, 0, 100, 100);
}

void ScoreBoard::updateScore(int s)
{
    scoreTextItem_->setPlainText("Score: " + QString::number(s));
    healthTextItem_->setPlainText("Health: " + QString::number(game->getShip()->health()));
}

int ScoreBoard::score()
{
    return scoreTextItem_->toPlainText().remove("Score: ").toInt();
}

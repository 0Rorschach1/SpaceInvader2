#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class ScoreBoard : public QGraphicsRectItem {
public:
    ScoreBoard();
    ScoreBoard(int s);
    void updateScore(int s);
    int score();

private:
    QGraphicsTextItem* scoreTextItem_;
    QGraphicsTextItem* healthTextItem_;
};

#endif // SCOREBOARD_H

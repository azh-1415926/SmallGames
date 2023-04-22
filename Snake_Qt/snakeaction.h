
#ifndef SNAKEACTION_H
#define SNAKEACTION_H


#include <QObject>
#include <QQueue>
#include <QPoint>

class SnakeAction : public QObject
{
    Q_OBJECT
public:
    SnakeAction(QObject* parent=nullptr);
signals:
    void moveHead(QPoint const& head);
    void moveTail(QPoint const& tail);
public slots:
    void initalSnake();
    void moveTo(int direction);
    void eatFood();
    void clearSnake();
private:
    int length;
    int lastLength;
    QPoint head;
    QPoint tail;
    QQueue<QPoint> snakeShape;
    void moveFront();
    void moveLeft();
    void moveRight();
    void moveBehind();
};

#endif // SNAKEACTION_H

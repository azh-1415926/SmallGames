
#include "snakeaction.h"
#include <QDebug>

SnakeAction::SnakeAction(QObject* parent)
    : QObject(parent)
{
    initalSnake();
}

void SnakeAction::initalSnake()
{
    length=lastLength=1;
    head.rx()=225;
    head.ry()=225;
}

void SnakeAction::moveTo(int direction)
{
    switch(direction){
    //front
    case 0:
        moveFront();
        qDebug()<<"move front";
        break;
    //right
    case 1:
        moveRight();
        qDebug()<<"move right";
        break;
    //behind
    case 2:
        moveBehind();
        qDebug()<<"move behind";
        break;
    //left
    case 3:
        moveLeft();
        qDebug()<<"move left";
        break;
    }
    emit moveHead(head);
    if(length==lastLength){
        snakeShape.enqueue(head);
        emit moveTail(snakeShape.dequeue());
    }else{
        lastLength++;
    }
}

void SnakeAction::eatFood(int pos)
{
    snakeShape.enqueue(QPoint(25+pos%9*50,25+pos/9*50));
    length++;
}

void SnakeAction::clearSnake()
{
    snakeShape.clear();
}

void SnakeAction::getLength()
{
    emit sendLength(length);
}

void SnakeAction::moveFront()
{
    head.ry()-=50;
}

void SnakeAction::moveLeft()
{
    head.rx()-=50;
}

void SnakeAction::moveRight()
{
    head.rx()+=50;
}

void SnakeAction::moveBehind()
{
    head.ry()+=50;
}

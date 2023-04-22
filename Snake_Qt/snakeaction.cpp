
#include "snakeaction.h"
#include <QDebug>

SnakeAction::SnakeAction(QObject *parent)
    : QObject(parent)
    , lastDirection(0)
    , length(2)
    , lastLength(1)
{
    head.rx()=225;
    head.ry()=225;
}

void SnakeAction::moveAction(QPoint const& point)
{
    //vertical 0
    //horizon 1
    int flag=(lastDirection==0||lastDirection==2)?0:1;
    if(point.x()>head.x()+50&&flag==0){
        //right
        lastDirection=1;
    }else if(point.x()<head.x()&&flag==0){
        //left
        lastDirection=3;
    }else if(point.y()>head.y()+50&&flag==1){
        //behind
        lastDirection=2;
    }else if(point.y()<head.y()&&flag==1){
        //front
        lastDirection=0;
    }else{
        //last
        //noaction
    }
    //moveTo(lastDirection);
}

void SnakeAction::moveTo(int direction)
{
again:
    switch(direction){
    //front
    case 0:
        moveFront();
        qDebug()<<"move front";
        lastDirection=0;
        break;
    //right
    case 1:
        moveRight();
        qDebug()<<"move right";
        lastDirection=1;
        break;
    //behind
    case 2:
        moveBehind();
        qDebug()<<"move behind";
        lastDirection=2;
        break;
    //left
    case 3:
        moveLeft();
        qDebug()<<"move left";
        lastDirection=3;
        break;
    default:
        direction=lastDirection;
        goto again;
    }
    emit moveHead(head);
    if(length==lastLength){
        snakeShape.enqueue(head);
        emit moveTail(snakeShape.dequeue());
    }else{
        lastLength++;
    }
}

void SnakeAction::eatFood()
{
    length++;
}

void SnakeAction::clearSnake()
{
    //emit removeBody(head);
    head.rx()=225;
    head.ry()=225;
    length=1;
    lastDirection=0;
    while(!snakeShape.isEmpty()){
        emit removeBody(snakeShape.dequeue());
    }
    //emit removeBody(tail);
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



#include "gamecontrol.h"
#include <QTimer>
#include <QDebug>

GameControl::GameControl(QObject* parent)
    : QObject(parent)
{
    lastDirection=0;
    head=tail=40;
}

void GameControl::timerEvent(QTimerEvent *event)
{
    emit moving(lastDirection);
}

void GameControl::startGame(){
    lastDirection=0;
    head=tail=40;
    timerId=startTimer(1000);
}

void GameControl::moveSnake(const QPoint &point)
{
    int flag=(lastDirection==0||lastDirection==2)?0:1;
    int row=head/9;
    int column=head%9;
    if(point.x()>25+column*50+50&&flag==0){
        //right
        lastDirection=1;
    }else if(point.x()<25+column*50&&flag==0){
        //left
        lastDirection=3;
    }else if(point.y()>25+row*50+50&&flag==1){
        //behind
        lastDirection=2;
    }else if(point.y()<25+row*50&&flag==1){
        //front
        lastDirection=0;
    }
}

void GameControl::updateHead(const QPoint &head)
{
    qDebug()<<"try to mouse head to "<<head;
    if(head.x()<25||head.x()>425||head.y()<25||head.y()>425){
        qDebug()<<"head error";
        emit exitGame();
        return;
    }
    int pos=(head.x()-25)/50+(head.y()-25)/50*9;
    qDebug()<<"head pos:"<<pos;
    emit moveHead(pos);
}

void GameControl::updateTail(const QPoint &tail)
{
    qDebug()<<"try to mouse tail to "<<tail;
    if(tail.x()<25||tail.x()>425||tail.y()<25||tail.y()>425){
        qDebug()<<"tail error";
        emit exitGame();
        return;
    }
    emit moveTail(this->tail);
    this->tail=(tail.x()-25)/50+(tail.y()-25)/50*9;
}

void GameControl::exitGame()
{
    killTimer(timerId);
}


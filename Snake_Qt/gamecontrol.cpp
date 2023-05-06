
#include "gamecontrol.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

GameControl::GameControl(QObject* parent)
    : QObject(parent)
    , startTime(0)
{
    lastDirection=0;
    head=tail=40;
}

void GameControl::timerEvent(QTimerEvent *event)
{
    emit moving(lastDirection);
    flag=0;
}

void GameControl::initalControl(){
    lastDirection=0;
    head=tail=40;
    timerId=startTimer(1000);
    flag=0;
    startTime=clock();
}

void GameControl::moveTo(int direction)
{
    if(this->flag){
        return;
    }
    this->flag=1;
    switch (direction) {
    case 0:
        if(lastDirection!=2){
            lastDirection=0;
        }
        break;
    case 1:
        if(lastDirection!=3){
            lastDirection=1;
        }
        break;
    case 2:
        if(lastDirection!=0){
            lastDirection=2;
        }
        break;
    case 3:
        if(lastDirection!=1){
            lastDirection=3;
        }
        break;
    }
}

void GameControl::moveSnake(const QPoint &point)
{
    if(this->flag){
        return;
    }
    this->flag=1;
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
        closeGame();
        return;
    }
    int pos=(head.x()-25)/50+(head.y()-25)/50*9;
    qDebug()<<"head pos:"<<pos;
    emit moveHead(pos);
    this->head=pos;
}

void GameControl::updateTail(const QPoint &tail)
{
    qDebug()<<"try to mouse tail to "<<tail;
    if(tail.x()<25||tail.x()>425||tail.y()<25||tail.y()>425){
        qDebug()<<"tail error";
        //emit exitGame();
        return;
    }
    emit moveTail(this->tail);
    this->tail=(tail.x()-25)/50+(tail.y()-25)/50*9;
}

void GameControl::closeGame()
{
    killTimer(timerId);
    emit costTime((clock()-startTime)/1000.0);
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!","Do you want play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Ok){
        emit restartGame();
    }else{
        emit exitGame();
    }
}


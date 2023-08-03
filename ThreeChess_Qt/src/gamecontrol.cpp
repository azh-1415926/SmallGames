#include "gamecontrol.h"
#include <QMessageBox>

GameControl::GameControl(QObject* parent)
    : QObject(parent)
    , playerColor(Qt::black)
    , computerColor(Qt::white)
    , currColor(qRgb(255,222,173))
    , gameFlag(0)
    , startTime(0)
    , endTime(0)
{
    srand(time(NULL));
}

void GameControl::initalGame()
{
    int option;
    if(gameFlag==0){
        option=QMessageBox::question(nullptr,"Game Initalize...","choose your chequer!","black chequer","white chequer");
        playerColor=option?Qt::white:Qt::black;
        computerColor=option?Qt::black:Qt::white;
        option=QMessageBox::question(NULL,"Game Initalize...","choose the first player!","your","computer");
        currColor=option?computerColor:playerColor;
    }else{
        gameFlag=0;
        emit restartGame();
        return;
    }
    gameFlag=1;
    startTime=clock();
    emit startGame();
}

void GameControl::settleGame(QString const& content)
{
    gameFlag=0;
    QString gamer=(content==",no one wins"?"null":(currColor==computerColor?"player":"computer"));
    currColor=qRgb(255,222,173);
    QMessageBox::StandardButton result=QMessageBox::question(nullptr,"Game Over",gamer+content+",Do you want to play again?",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Yes){
        emit restartGame();
    }else{
        emit closeGame();
    }
    endTime=clock();
    emit record(gamer,endTime-startTime);
}

void GameControl::getOption(int pos)
{
    if(gameFlag==0){
        qDebug()<<"return error pos:"<<pos;
        return;
    }
    if(currColor==computerColor&&pos==-1){
        pos=computerOption();
        qDebug()<<"getComputerOption:"<<pos;
    }else if(currColor==playerColor&&pos!=-1){
        qDebug()<<"getPlayerOption:"<<pos;
    }else{
        return;
    }
    emit sendOption(pos,currColor);
}

void GameControl::switchNextGamer()
{
    qDebug()<<"switch next gamer,color:"<<currColor;
    currColor=(currColor==playerColor?computerColor:playerColor);
}
int GameControl::computerOption(){
    return rand()%9;
}

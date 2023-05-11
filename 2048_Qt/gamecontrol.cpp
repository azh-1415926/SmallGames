
#include "gamecontrol.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

GameControl::GameControl(QObject* parent)
    : QObject(parent)
    , startTime(0)
    , flag(0)
    , maxNumber(0)
    , totalScore(0)
    , zeroCount(16)
{
    srand(time(NULL));
}

void GameControl::initalControl(){
    if(zeroCount!=16){
        killTimer(timerId);
        flag=0;
        maxNumber=0;
        totalScore=0;
        zeroCount=16;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                array[i][j]=0;
            }
        }
    }
    timerId=startTimer(500);
    startTime=clock();
    addNumber();
    addNumber();
}

void GameControl::moving(int direction)
{
    if(flag){
        return;
    }
    setFlag();
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
    addNumber();
    if(maxNumber==2048){
        //win
        killTimer(timerId);
        emit costTime((clock()-startTime)/1000.0);
        QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!","You win!Do you want play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
        if(result==QMessageBox::Ok){
            emit restartGame();
        }else{
            emit exitGame();
        }
    }else if(zeroCount==0){
        if(isOver()){
            closeGame();
        }
    }
    qDebug()<<"----------------";
    for(int i=0;i<4;i++){
        qDebug()<<"|"<<array[i][0]<<"|"<<array[i][1]<<"|"<<array[i][2]<<"|"<<array[i][3]<<"|";
    }
    qDebug()<<"----------------";
//    for(int i=0;i<4;i++){
//        for(int j=0;j<4;j++){
//            if(array[i][j]==0){
//                emit delPoint(i*4+j);
//            }else{
//                emit addPoint(i*4+j,array[i][j]);
//            }
//        }
//    }
}

void GameControl::addNumber()
{
    int pos=-1;
    int num=-1;
    while(pos==-1||pos!=-1&&array[pos/4][pos%4]!=0){
        pos=rand()%16;
        if(zeroCount==0){
            return;
        }
    }
    num=(rand()%2+1)*2;
    array[pos/4][pos%4]=num;
    emit addPoint(pos,num);
    zeroCount--;
}

void GameControl::updateScore(int score)
{
    if(score>maxNumber){
        maxNumber=score;
    }
    totalScore+=score;
    zeroCount++;
}

void GameControl::setFlag()
{
    flag=1;
}

void GameControl::resetFlag()
{
    flag=0;
}

void GameControl::closeGame()
{
    killTimer(timerId);
    flag=0;
    maxNumber=0;
    totalScore=0;
    zeroCount=16;
    emit costTime((clock()-startTime)/1000.0);
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!","You failed!Do you want play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Ok){
        emit restartGame();
    }else{
        emit exitGame();
    }
}

void GameControl::timerEvent(QTimerEvent *event)
{
    resetFlag();
}

void GameControl::moveFront(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[j][i]!=0&&array[j][i]==array[j-k][i]){
                    updateScore(array[j][i]);
                    array[j-k][i]=0;
                    array[j][i]*=2;
                    emit delPoint((j-k)*4+i);
                    emit addPoint(j*4+i,array[j][i]);
                    k++;
                }else if(array[j-k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(array[j][i]==0){
                for(int k=j+1;k<4;k++){
                    if(array[k][i]!=0){
                        array[j][i]=array[k][i];
                        array[k][i]=0;
                        emit addPoint(j*4+i,array[j][i]);
                        emit delPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}
void GameControl::moveLeft(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[i][j]!=0&&array[i][j]==array[i][j-k]){
                    updateScore(array[j][i]);
                    array[i][j-k]=0;
                    array[i][j]*=2;
                    emit delPoint(i*4+j-k);
                    emit addPoint(i*4+j,array[i][j]);
                    k++;
                }else if(array[i][j-k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(array[i][j]==0){
                for(int k=j+1;k<4;k++){
                    if(array[i][k]!=0){
                        array[i][j]=array[i][k];
                        array[i][k]=0;
                        emit addPoint(i*4+j,array[i][j]);
                        emit delPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}
void GameControl::moveRight(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[i][j]!=0&&array[i][j]==array[i][j+k]){
                    updateScore(array[j][i]);
                    array[i][j+k]=0;
                    array[i][j]*=2;
                    emit delPoint(i*4+j+k);
                    emit addPoint(i*4+j,array[i][j]);
                    k++;
                }else if(array[i][j+k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(array[i][j]==0){
                for(int k=j-1;k>=0;k--){
                    if(array[i][k]!=0){
                        array[i][j]=array[i][k];
                        array[i][k]=0;
                        emit addPoint(i*4+j,array[i][j]);
                        emit delPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}
void GameControl::moveBehind(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[j][i]!=0&&array[j][i]==array[j+k][i]){
                    updateScore(array[j][i]);
                    array[j+k][i]=0;
                    array[j][i]*=2;
                    emit delPoint((j+k)*4+i);
                    emit addPoint(j*4+i,array[j][i]);
                    k++;
                }else if(array[j+k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(array[j][i]==0){
                for(int k=j-1;k>=0;k--){
                    if(array[k][i]!=0){
                        array[j][i]=array[k][i];
                        array[k][i]=0;
                        emit addPoint(j*4+i,array[j][i]);
                        emit delPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}

bool GameControl::isOver()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i+1<4&&array[i][j]==array[i+1][j]){
                return false;
            }
            if(j+1<4&&array[i][j]==array[i][j+1]){
                return false;
            }
        }
    }
    memset(array,0,sizeof(array));
    emit sendScore(totalScore);
    return true;
}

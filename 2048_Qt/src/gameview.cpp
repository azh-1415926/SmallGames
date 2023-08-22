#include "gameview.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

gameView::gameView(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene,this))
    , group(new QGraphicsItemGroup)
    , startTime(0)
    , flagOfTime(0)
    , maxNumber(0)
    , zeroCount(16)
{
    initalView();
    initalGame();
    startGame();
}

gameView::~gameView()
{
    delete scene;
    delete group;
}

void gameView::timerEvent(QTimerEvent *event)
{
    flagOfTime=0;
}

void gameView::startGame()
{
    if(zeroCount!=16)
        clearView();
    timerId=startTimer(250);
    startTime=clock();
    addNumber();
}

void gameView::updatePoint(int pos,int num)
{
    if(blocks[pos]==nullptr){
        blocks[pos]=new QGraphicsRectItem(50+pos%4*100,50+pos/4*100,100,100);
        group->addToGroup(blocks[pos]);
    }
    QString str=QString::number(num);
    qreal offset=(4-str.length())/2.0*25;
    numbers[pos]->setPlainText(str);
    numbers[pos]->setPos(50+pos%4*100+offset,75+pos/4*100);
    blocks[pos]->setBrush(getBrushByNum(num));
}

void gameView::clearPoint(int pos)
{
    if(blocks[pos]!=nullptr){
        delete blocks[pos];
        blocks[pos]=nullptr;
        numbers[pos]->setPlainText("");
    }
}

void gameView::clearView()
{
    for(int i=0;i<16;i++){
        if(blocks[i]!=nullptr){
            delete blocks[i];
            blocks[i]=nullptr;
            numbers[i]->setPlainText("");
        }
    }
    killTimer(timerId);
    flagOfTime=0;
    maxNumber=0;
    zeroCount=16;
    memset(array,0,sizeof(array));
}

void gameView::moveTo(int direction)
{
    if(flagOfTime==1){
        return;
    }
    flagOfTime=1;
    static int preDirection;
    switch(direction){
    case 0:
        moveFront();
        qDebug()<<"move front";
        break;
    case 1:
        moveRight();
        qDebug()<<"move right";
        break;
    case 2:
        moveBehind();
        qDebug()<<"move behind";
        break;
    case 3:
        moveLeft();
        qDebug()<<"move left";
        break;
    }
    if(zeroCount>=15||preDirection!=direction)
        addNumber();
    preDirection=direction;
    qDebug()<<"----gameInfo----";
    for(int i=0;i<4;i++){
        qDebug()<<"|"<<array[i][0]<<"|"<<array[i][1]<<"|"<<array[i][2]<<"|"<<array[i][3]<<"|";
    }
    qDebug()<<"----------------";
    if(maxNumber>=2048||zeroCount==0)
        settleGame();
}

void gameView::settleGame()
{
    if(maxNumber<2048&&!isOver())
        return;
    QString tip;
    if(maxNumber>=2048)
        tip.append("You win ! Do you want play again?");
    else if(zeroCount==0)
        tip.append("You failed ! Do you want play again?");
    emit settleTime((clock()-startTime)/1000.0);
    updateScore(-1);
    QMessageBox::Button result;
    result=QMessageBox::question(nullptr,"Game Over!",tip,QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Ok)
        startGame();
    else{
        clearView();
        emit closeGame();
    }
}

void gameView::initalView()
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    view->setBackgroundBrush(QBrush(qRgb(238,232,170)));
    layout->addWidget(view);
    for(int i=150;i<475;i=i+100)
        group->addToGroup(new QGraphicsLineItem(i,50,i,450));
    for(int i=150;i<475;i=i+100)
        group->addToGroup(new QGraphicsLineItem(50,i,450,i));
    QGraphicsRectItem* rect=new QGraphicsRectItem(50,50,400,400);
    group->addToGroup(rect);
    scene->addItem(group);
}

void gameView::initalGame()
{
    srand(time(NULL));
    for(int i=0;i<16;i++){
        blocks<<nullptr;
        numbers<<new QGraphicsTextItem;
        QFont font;
        font.setPointSize(25);
        numbers[i]->setFont(font);
        numbers[i]->setPos(50+i%4*100,75+i/4*100);
        numbers[i]->setZValue(22);
        group->addToGroup(numbers[i]);
    }
}


void gameView::addNumber()
{
    int pos=-1;
    int num=-1;
    while(pos==-1||pos!=-1&&array[pos/4][pos%4]!=0){
        pos=rand()%16;
        if(zeroCount==0)
            return;
    }
    num=(rand()%2+1)*2;
    array[pos/4][pos%4]=num;
    updatePoint(pos,num);
    zeroCount--;
}

void gameView::updateScore(int score)
{
    static int totalScore;
    if(score==-1){
        emit settleScore(totalScore);
        return;
    }
    if(score>maxNumber/2)
        maxNumber=score*2;
    totalScore+=score;
    zeroCount++;
}

QBrush gameView::getBrushByNum(int i)
{
    switch (i) {
    case 2:
        //玉米丝
        return QBrush(qRgb(255,248,220));
        break;
    case 4:
        //杏仁变白
        return QBrush(qRgb(255,235,205));
        break;
    case 8:
        //浓汤
        return QBrush(qRgb(255,228,196));
        break;
    case 16:
        //小麦
        return QBrush(qRgb(245,222,179));
        break;
    case 32:
        //棕褐色
        return QBrush(qRgb(210,180,140));
        break;
    case 64:
        //魁梧的木头
        return QBrush(qRgb(222,184,135));
        break;
    case 128:
        //沙棕色
        return QBrush(qRgb(244,164,96));
        break;
    case 256:
        //秘鲁
        return QBrush(qRgb(205,133,63));
        break;
    case 512:
        //巧克力
        return QBrush(qRgb(210,105,30));
        break;
    case 1024:
        //赭色
        return QBrush(qRgb(160,82,45));
        break;
    case 2048:
        //鞍棕色
        return QBrush(qRgb(139,69,19));
        break;
    default:
        break;
    }
    return QBrush();
}

void gameView::moveFront()
{
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[j][i]!=0&&array[j][i]==array[j-k][i]){
                    updateScore(array[j][i]);
                    array[j-k][i]=0;
                    array[j][i]*=2;
                    updatePoint(j*4+i,array[j][i]);
                    clearPoint((j-k)*4+i);
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
                        updatePoint(j*4+i,array[j][i]);
                        clearPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}

void gameView::moveLeft()
{
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[i][j]!=0&&array[i][j]==array[i][j-k]){
                    updateScore(array[i][j]);
                    array[i][j-k]=0;
                    array[i][j]*=2;
                    updatePoint(i*4+j,array[i][j]);
                    clearPoint(i*4+j-k);
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
                        updatePoint(i*4+j,array[i][j]);
                        clearPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}

void gameView::moveRight()
{
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[i][j]!=0&&array[i][j]==array[i][j+k]){
                    updateScore(array[i][j]);
                    array[i][j+k]=0;
                    array[i][j]*=2;
                    updatePoint(i*4+j,array[i][j]);
                    clearPoint(i*4+j+k);
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
                        updatePoint(i*4+j,array[i][j]);
                        clearPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}

void gameView::moveBehind()
{
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[j][i]!=0&&array[j][i]==array[j+k][i]){
                    updateScore(array[j][i]);
                    array[j+k][i]=0;
                    array[j][i]*=2;
                    updatePoint(j*4+i,array[j][i]);
                    clearPoint((j+k)*4+i);
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
                        updatePoint(j*4+i,array[j][i]);
                        clearPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}

bool gameView::isOver()
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
    return true;
}
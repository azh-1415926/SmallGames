#include "gameview.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>

gameView::gameView(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene,this))
    , flagOfGame(0)
    , currColor(qRgb(255,222,173))
    , colorOfChequer(Qt::black,Qt::white)
{
    initalView();
    initalGame();
}

gameView::~gameView()
{
    
}

void gameView::mousePressEvent(QMouseEvent* event)
{
    qreal x,y;
    #if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
        x=event->pos().x();
        y=event->pos().y();
    #elif (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        x=event->position().x();
        y=event->position().y();
    #endif
    clickPoint(QPoint(x,y));
}

void gameView::clickPoint(const QPoint &p)
{
    int pos=getPlayerOptionByPoint(p);
    if(pos==-1)
        return;
    addChequer(pos);
}

void gameView::getOptionAgain()
{
    if(currColor==colorOfChequer.second)
        addChequer(-1);
}

void gameView::startGame()
{
    if(flagOfGame==1)
        clearView();
    int option=-1;
    if(flagOfGame==0){
        option=QMessageBox::question(nullptr,"Game Initalize...","choose your chequer!","black chequer","white chequer");
        colorOfChequer.first=option?Qt::white:Qt::black;
        colorOfChequer.second=option?Qt::black:Qt::white;
        option=QMessageBox::question(NULL,"Game Initalize...","choose the first player!","your","computer");
        currColor=option?colorOfChequer.second:colorOfChequer.first;
        // currColor=option?colorOfChequer.first:colorOfChequer.second;
    }
    flagOfGame=1;
    startTime=clock();
    // currColor=qRgb(255,222,173);
    addChequer(-1);
}

void gameView::initalView()
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->addWidget(view);
    view->setWindowTitle("Three Chess");
    view->resize(500,500);
    view->setBackgroundBrush(QBrush(QColor(qRgb(255,222,173))));
    QPen pen(Qt::DotLine);
    group=new QGraphicsItemGroup;
    QGraphicsLineItem* line=nullptr;
    QRect range(100,100,300,300);
    qreal n=2.0;
    qreal gapOfX=range.width()/(n+1);
    qreal gapOfY=range.height()/(n+1);
    group->addToGroup(new QGraphicsRectItem(range));
    qreal x=range.x()+gapOfX;
    qreal y=range.y()+gapOfY;
        for(;x<range.x()+range.width()&&y<range.y()+range.height();x+=gapOfX,y+=gapOfY){
            line=new QGraphicsLineItem(range.x(),y,range.x()+range.width(),y);
            line->setPen(pen);
            group->addToGroup(line);
            line=new QGraphicsLineItem(x,range.y(),x,range.y()+range.height());
            line->setPen(pen);
            group->addToGroup(line);
        }
    scene->addItem(group);
}

void gameView::initalGame()
{
    srand(time(NULL));
    for(int i=0;i<9;i++)
        chequers<<nullptr;
}

void gameView::clearView(){
    for(int i=0;i<9;i++){
        if(chequers[i]!=nullptr){
            delete chequers[i];
            chequers[i]=nullptr;
        }
    }
    flagOfGame=0;
}

void gameView::addChequer(int pos)
{
    if(flagOfGame==0){
        qDebug()<<"return error pos:"<<pos;
        return;
    }
    if(currColor==colorOfChequer.second){
        pos=getComputerOption();
        qDebug()<<"getComputerOption:"<<pos;
    }else if(currColor==colorOfChequer.first&&pos!=-1){
        qDebug()<<"getPlayerOption:"<<pos;
    }
    if(pos==-1||chequers[pos]!=nullptr){
        pos=chequers.indexOf(nullptr);
        if(pos!=-1)
            getOptionAgain();
        return;
    }
    setChequer(pos);
}

void gameView::switchNextPlayer()
{
    qDebug()<<"switch next gamer,color:"<<currColor;
    currColor=(currColor==colorOfChequer.first?colorOfChequer.second:colorOfChequer.first);
}

int gameView::getComputerOption(){
    return rand()%9;
}

void gameView::setChequer(int pos)
{
    int row=pos/3;
    int column=pos%3;
    chequers[pos]=new QGraphicsEllipseItem;
    chequers[pos]->setRect(115+column*100,115+row*100,70,70);
    chequers[pos]->setBrush(QBrush(currColor));
    scene->addItem(chequers[pos]);
    if(isWin(pos)){
        settleGame(" is wins!");
        return;
    }else{
        for(int i=0;i<9;i++){
            if(chequers[i]==nullptr)
                break;
            if(i==8){
                settleGame("no one wins");
                return;
            } 
        }
    }
    switchNextPlayer();
    getOptionAgain();
}

int gameView::getPlayerOptionByPoint(const QPoint& p)
{
    int x=p.x(),y=p.y();
    if(x>100&&x<400&&y>100&&y<400){
        if(x>100&&x<200){
            if(y>100&&y<200){
                return 0;
            }else if(y>200&&y<300){
                return 3;
            }else if(y>300&&y<400){
                return 6;
            }
        }else if(x>200&&x<300){
            if(y>100&&y<200){
                return 1;
            }else if(y>200&&y<300){
                return 4;
            }else if(y>300&&y<400){
                return 7;
            }
        }else if(x>300&&x<400){
            if(y>100&&y<200){
                return 2;
            }else if(y>200&&y<300){
                return 5;
            }else if(y>300&&y<400){
                return 8;
            }
        }
    }
    return -1;
}

bool gameView::isWin(int pos)
{
    int row=pos/3;
    int column=pos%3;
    int count=1;
    int maxcount=1;
    const QColor& color=chequers[pos]->brush().color();
    for(int i=1;i<3;++i){
        if(chequers[(row+i)%3*3+column]==nullptr)
            break;
        if(color==chequers[(row+i)%3*3+column]->brush().color())
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3;++i){
        if(chequers[row*3+(column+i)%3]==nullptr)
            break;
        if(color==chequers[row*3+(column+i)%3]->brush().color())
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3&&(row==column);++i){
        if(chequers[(row+i)%3*3+(column+i)%3]==nullptr)
            break;
        if(color==chequers[(row+i)%3*3+(column+i)%3]->brush().color())
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3&&((row+column)==2);++i){
        if(chequers[(row+i)%3*3+(column+2*i)%3]==nullptr)
            break;
        if(color==chequers[(row+i)%3*3+(column+2*i)%3]->brush().color())
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    if(maxcount==3){
        return true;
    }
    return false;
}

void gameView::settleGame(const QString &tip)
{
    QString player=(currColor==colorOfChequer.first)?("player"):("computer");
    if(tip=="no one wins")
        player="";
    emit settlePlayer(player);
    emit settleTime((clock()-startTime)/1000.0);
    QMessageBox::Button result;
    result=QMessageBox::question(nullptr,"Game Over!",player+tip,QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Ok)
        startGame();
    else{
        clearView();
        emit closeGame();
    }
}
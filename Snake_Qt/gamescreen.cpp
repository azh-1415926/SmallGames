
#include "gamescreen.h"
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QDebug>

GameScreen::GameScreen(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(scene,this))
    , group(new QGraphicsItemGroup)
{
    view->resize(500,500);
    view->setWindowTitle("Snake");
    view->setBackgroundBrush(QBrush(qRgb(107,142,35)));
    initalGame();
    head=new QGraphicsRectItem(225,225,50,50);
    head->setBrush(QBrush(Qt::yellow));
    tail=head;
    group->addToGroup(head);
    for(int i=0;i<81;i++){
        snakeShape<<nullptr;
    }
}

void GameScreen::updateHead(QPoint const& head)
{
    //vaild range:25,25-425,425
    //(x-25)/50,(y-25)/50:0,0-8,8
    //index:0-81
    qDebug()<<"try to mouse head to "<<head;
    if(head.x()<25||head.x()>425||head.y()<25||head.y()>425){
        qDebug()<<"head error";
        emit closeGame();
        this->head=this->tail=nullptr;
        return;
    }
    int pos=(head.x()-25)/50+(head.y()-25)/50*9;
    qDebug()<<"head pos:"<<pos;
    if(snakeShape[pos]!=nullptr){
        qDebug()<<"head error";
        emit closeGame();
        this->head=this->tail=nullptr;
        return;
    }
    snakeShape[pos]=new QGraphicsRectItem(head.x(),head.y(),50,50);
    snakeShape[pos]->setBrush(QBrush(Qt::yellow));
    this->head=snakeShape[pos];
    group->addToGroup(snakeShape[pos]);
}

void GameScreen::updateTail(QPoint const& tail)
{
    qDebug()<<"try to mouse tail to "<<tail;
    if(tail.x()<25||tail.x()>425||tail.y()<25||tail.y()>425){
        qDebug()<<"tail error";
        emit closeGame();
        this->head=this->tail=nullptr;
        return;
    }
    int pos=(tail.x()-25)/50+(tail.y()-25)/50*9;
    qDebug()<<"tail pos:"<<pos;
    if(snakeShape[pos]==nullptr){
        //error
        emit closeGame();
        this->head=this->tail=nullptr;
        return;
    }
    QRectF rectf=this->tail->rect();
    qDebug()<<"tail:"<<rectf;
    //removePoint(QPoint(rectf.x(),rectf.y()));
    int lastpos=(rectf.x()-25)/50+(rectf.y()-25)/50*9;
    delete this->tail;
    this->tail=snakeShape[pos];
    snakeShape[lastpos]=nullptr;
//    int lastpos=(rectf.x()-25)/50+(rectf.y()-25)/50*9;
//    delete snakeShape[lastpos];
//    snakeShape[lastpos]=nullptr;
    this->tail=snakeShape[pos];
}

void GameScreen::removePoint(QPoint const& point){
    int pos=(point.x()-25)/50+(point.y()-25)/50*9;
    delete snakeShape[pos];
    snakeShape[pos]=nullptr;
}

void GameScreen::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse press on the "<<event->position().x()<<" "<<event->position().y();
    emit clickScreen(QPoint(event->position().x(),event->position().y()));
}

void GameScreen::initalGame()
{
    for(int i=75;i<500;i=i+50){
        group->addToGroup(new QGraphicsLineItem(i,25,i,475));
    }
    for(int i=75;i<500;i=i+50){
        group->addToGroup(new QGraphicsLineItem(25,i,475,i));
    }
    QGraphicsRectItem* rect=new QGraphicsRectItem(25,25,450,450);
    QPen pen;
    //pen.setWidth(6);
    rect->setPen(pen);
    group->setScale(1.0);
    group->addToGroup(rect);
    scene->addItem(group);
}

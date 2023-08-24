#include "gameview.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

gameView::gameView(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene,this))
    , startTime(0)
    , flagOfGame(0)
    , flagOfTime(0)
    , food(nullptr)
{
    initalView();
    initalGame();
}

gameView::~gameView()
{
    delete scene;
    delete group;
}

void gameView::timerEvent(QTimerEvent *e)
{
    moving(lastDirection);
    flagOfTime=0;
}

void gameView::closeEvent(QCloseEvent *e)
{
    clearView();
}

void gameView::startGame(){
    if(flagOfGame==1)
        clearView();
    timerId=startTimer(1000);
    startTime=clock();
    lastDirection=0;
    head=tail=40;
    flagOfGame=1;
    flagOfTime=0;
    updatePoint(40);
    addFood();
}

void gameView::clickPoint(const QPoint &p)
{
    if(flagOfGame==0||flagOfTime==1)
        return;
    flagOfTime=1;
    int flag=(lastDirection==0||lastDirection==2)?0:1;
    int row=head/9;
    int column=head%9;
    if(p.x()>25+column*50+50&&flag==0){
        //right
        lastDirection=1;
    }else if(p.x()<25+column*50&&flag==0){
        //left
        lastDirection=3;
    }else if(p.y()>25+row*50+50&&flag==1){
        //behind
        lastDirection=2;
    }else if(p.y()<25+row*50&&flag==1){
        //front
        lastDirection=0;
    }
}

void gameView::moveTo(int direction)
{
    if(flagOfGame==0||flagOfTime==1)
        return;
    flagOfTime=1;
    switch (direction) {
    case 0:
        if(lastDirection!=2)
            lastDirection=0;
        break;
    case 1:
        if(lastDirection!=3)
            lastDirection=1;
        break;
    case 2:
        if(lastDirection!=0)
            lastDirection=2;
        break;
    case 3:
        if(lastDirection!=1)
            lastDirection=3;
        break;
    }
}

void gameView::moving(int direction)
{
    static QPoint p;
    p.rx()=25+head%9*50;
    p.ry()=25+head/9*50;
    switch(direction){
    case 0:
        qDebug()<<"move front";
        p.ry()-=50;
        break;
    case 1:
        qDebug()<<"move right";
        p.rx()+=50;
        break;
    case 2:
        qDebug()<<"move behind";
        p.ry()+=50;
        break;
    case 3:
        qDebug()<<"move left";
        p.rx()-=50;
        break;
    default:
        return;
    }
    snake.enqueue(p);
    updateHead(p);
}

void gameView::updateHead(const QPoint& head)
{
    qDebug()<<"try to mouse head to "<<head;
    if(head.x()<25||head.x()>425||head.y()<25||head.y()>425){
        qDebug()<<"head error";
        settleGame();
        return;
    }
    int pos=(head.x()-25)/50+(head.y()-25)/50*9;
    qDebug()<<"head pos:"<<pos;
    if(snakeShape[pos]==food){
        food->setBrush(Qt::yellow);
        food=nullptr;
    }
    updatePoint(pos);
    if(flagOfGame==1){
        if(food==nullptr)
            addFood();
        else
            updateTail(snake.dequeue());
        this->head=pos;
    }else{
        settleGame();
    }
}

void gameView::updateTail(const QPoint& tail)
{
    qDebug()<<"try to mouse tail to "<<tail;
    if(tail.x()<25||tail.x()>425||tail.y()<25||tail.y()>425){
        qDebug()<<"tail error";
        return;
    }
    clearPoint(this->tail);
    this->tail=(tail.x()-25)/50+(tail.y()-25)/50*9;
}

void gameView::updatePoint(int pos)
{
    int row=pos/9;
    int column=pos%9;
    if(snakeShape[pos]==nullptr){
        snakeShape[pos]=new QGraphicsRectItem(25+column*50,25+row*50,50,50);
        snakeShape[pos]->setBrush(QBrush(Qt::yellow));
        group->addToGroup(snakeShape[pos]);
    }else if(food!=nullptr){
        flagOfGame=0;
    }
}

void gameView::clearPoint(int pos)
{
    if(snakeShape[pos]!=nullptr){
        delete snakeShape[pos];
        snakeShape[pos]=nullptr;
    }
}

void gameView::addFood()
{
    int pos=-1;
    while(pos==-1||snakeShape[pos]!=nullptr){
        pos=rand()%81;
        if(snakeShape.indexOf(nullptr)==-1)
            return;
    }
    snakeShape[pos]=new QGraphicsRectItem(25+pos%9*50,25+pos/9*50,50,50);
    snakeShape[pos]->setBrush(Qt::gray);
    group->addToGroup(snakeShape[pos]);
    food=snakeShape[pos];
}

void gameView::initalView()
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    view->resize(500,500);
    view->setWindowTitle("Snake");
    view->setBackgroundBrush(QBrush(qRgb(107,142,35)));
    group=new QGraphicsItemGroup;
    QGraphicsLineItem* line=nullptr;
    QRect range(25,25,450,450);
    qreal n=8.0;
    qreal gapOfX=range.width()/(n+1);
    qreal gapOfY=range.height()/(n+1);
    group->addToGroup(new QGraphicsRectItem(range));
    qreal x=range.x()+gapOfX;
    qreal y=range.y()+gapOfY;
    for(;x<range.x()+range.width()&&y<range.y()+range.height();x+=gapOfX,y+=gapOfY){
        line=new QGraphicsLineItem(range.x(),y,range.x()+range.width(),y);
        group->addToGroup(line);
        line=new QGraphicsLineItem(x,range.y(),x,range.y()+range.height());
        group->addToGroup(line);
    }
    scene->addItem(group);
    layout->addWidget(view);
}

void gameView::initalGame()
{
    srand(time(NULL));
    for(int i=0;i<81;i++)
        snakeShape<<nullptr;
}

void gameView::clearView()
{
    killTimer(timerId);
    for(int i=0;i<81;i++){
        if(snakeShape[i]!=nullptr){
            delete snakeShape[i];
            snakeShape[i]=nullptr;
        }
    }
    food=nullptr;
    snake.clear();
    flagOfGame=0;
}

void gameView::settleGame()
{
    emit settleTime((clock()-startTime)/1000.0);
    emit settleLength(snake.length());
    clearView();
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!","Do you want play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    if(result==QMessageBox::Ok){
        startGame();
        return;
    }
    emit closeGame();
}
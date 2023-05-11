
#include "gamescreen.h"
#include <QMouseEvent>

GameScreen::GameScreen(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene,this))
    , group(new QGraphicsItemGroup)
    , food(nullptr)
{
    //setFocusPolicy(Qt::StrongFocus);
    inital();
    for(int i=0;i<81;i++){
        snakeShape<<nullptr;
    }
}

void GameScreen::initalScreen(){
    if(food!=nullptr){
        clearScreen();
    }
    addFood();
    updatePoint(40);
    show();
}

void GameScreen::updatePoint(int pos)
{
    int row=pos/9;
    int column=pos%9;
    if(snakeShape[pos]==nullptr){
        snakeShape[pos]=new QGraphicsRectItem(25+column*50,25+row*50,50,50);
        snakeShape[pos]->setBrush(QBrush(Qt::yellow));
        group->addToGroup(snakeShape[pos]);
    }else if(snakeShape[pos]==food){
        food->setBrush(Qt::yellow);
        food=nullptr;
        addFood();
        emit findFood(pos);
    }else{
        emit closeGame();
    }
}

void GameScreen::clearPoint(int pos)
{
    if(snakeShape[pos]!=nullptr){
        delete snakeShape[pos];
        snakeShape[pos]=nullptr;
    }
}

void GameScreen::addFood()
{
    int pos=-1;
    while(pos==-1||snakeShape[pos]!=nullptr){
        pos=rand()%81;
    }
    snakeShape[pos]=new QGraphicsRectItem(25+pos%9*50,25+pos/9*50,50,50);
    snakeShape[pos]->setBrush(Qt::gray);
    group->addToGroup(snakeShape[pos]);
    food=snakeShape[pos];
}

void GameScreen::clearScreen()
{
    for(int i=0;i<81;i++){
        if(snakeShape[i]!=nullptr){
            delete snakeShape[i];
            snakeShape[i]=nullptr;
        }
    }
}

void GameScreen::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"mouse press on the "<<event->position().x()<<" "<<event->position().y();
    emit clickScreen(QPoint(event->position().x(),event->position().y()));
}

void GameScreen::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"press up";
        break;
    case Qt::Key_Down:
        qDebug()<<"press down";
        break;
    case Qt::Key_Left:
        qDebug()<<"press left";
        break;
    case Qt::Key_Right:
        qDebug()<<"press right";
        break;
    default:
        break;
    }
}
void GameScreen::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"release up";
        emit pressKeyboard(0);
        break;
    case Qt::Key_Down:
        qDebug()<<"release down";
        emit pressKeyboard(2);
        break;
    case Qt::Key_Left:
        qDebug()<<"release left";
        emit pressKeyboard(3);
        break;
    case Qt::Key_Right:
        qDebug()<<"release right";
        emit pressKeyboard(1);
        break;
    default:
        break;
    }
}

void GameScreen::inital()
{
    view->resize(500,500);
    view->setWindowTitle("Snake");
    view->setBackgroundBrush(QBrush(qRgb(107,142,35)));
    for(int i=75;i<500;i=i+50){
        group->addToGroup(new QGraphicsLineItem(i,25,i,475));
    }
    for(int i=75;i<500;i=i+50){
        group->addToGroup(new QGraphicsLineItem(25,i,475,i));
    }
    QGraphicsRectItem* rect=new QGraphicsRectItem(25,25,450,450);
    group->addToGroup(rect);
    scene->addItem(group);
    srand(time(NULL));
}


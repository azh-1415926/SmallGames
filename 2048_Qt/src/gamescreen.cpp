
#include "gamescreen.h"
#include <QMouseEvent>

GameScreen::GameScreen(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene,this))
    , group(new QGraphicsItemGroup)
{
    //setFocusPolicy(Qt::StrongFocus);
    initalScreen();
    for(int i=0;i<16;i++){
        background<<nullptr;
        number<<new QLabel(this);
        QFont font;
        font.setPointSize(25);
        number[i]->setFont(font);
        number[i]->setGeometry(50+i%4*100,50+i/4*100,100,100);
        number[i]->setAlignment(Qt::AlignCenter);
    }
}

GameScreen::~GameScreen()
{
    delete scene;
    delete group;
}

void GameScreen::updatePoint(int pos,int num)
{
    if(background[pos]==nullptr){
        background[pos]=new QGraphicsRectItem(50+pos%4*100,50+pos/4*100,100,100);
        group->addToGroup(background[pos]);
    }
    number[pos]->setText(QString().number(num));
    switch (num) {
    case 2:
        //玉米丝
        background[pos]->setBrush(QBrush(qRgb(255,248,220)));
        break;
    case 4:
        //杏仁变白
        background[pos]->setBrush(QBrush(qRgb(255,235,205)));
        break;
    case 8:
        //浓汤
        background[pos]->setBrush(QBrush(qRgb(255,228,196)));
        break;
    case 16:
        //小麦
        background[pos]->setBrush(QBrush(qRgb(245,222,179)));
        break;
    case 32:
        //棕褐色
        background[pos]->setBrush(QBrush(qRgb(210,180,140)));
        break;
    case 64:
        //魁梧的木头
        background[pos]->setBrush(QBrush(qRgb(222,184,135)));
        break;
    case 128:
        //沙棕色
        background[pos]->setBrush(QBrush(qRgb(244,164,96)));
        break;
    case 256:
        //秘鲁
        background[pos]->setBrush(QBrush(qRgb(205,133,63)));
        break;
    case 512:
        //巧克力
        background[pos]->setBrush(QBrush(qRgb(210,105,30)));
        break;
    case 1024:
        //赭色
        background[pos]->setBrush(QBrush(qRgb(160,82,45)));
        break;
    case 2048:
        //鞍棕色
        background[pos]->setBrush(QBrush(qRgb(139,69,19)));
        break;
    default:
        break;
    }
}

void GameScreen::clearPoint(int pos)
{
    if(background[pos]!=nullptr){
        delete background[pos];
        background[pos]=nullptr;
        number[pos]->setText("");
    }
}

void GameScreen::clearScreen()
{
    for(int i=0;i<16;i++){
        if(background[i]!=nullptr){
            delete background[i];
            background[i]=nullptr;
            number[i]->setText("");
        }
    }
}

void GameScreen::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"mouse press on the "<<event->position().x()<<" "<<event->position().y();
    clickPoint.rx()=event->position().x();
    clickPoint.ry()=event->position().y();
    grabMouse();
}

void GameScreen::mouseReleaseEvent(QMouseEvent *event)
{
    releaseMouse();
    qDebug()<<"mouse release on the "<<event->position().x()<<" "<<event->position().y();
    double k=(event->position().y()-clickPoint.y())/(event->position().x()-clickPoint.x());
    if((k>1||k<-1)&&event->position().y()<clickPoint.y()){
        qDebug()<<"got to front";
        emit goTo(0);
    }else if(k<1&&k>-1&&event->position().x()>clickPoint.x()){
        qDebug()<<"got to right";
        emit goTo(1);
    }else if((k>1||k<-1)&&event->position().y()>clickPoint.y()){
        qDebug()<<"got to behind";
        emit goTo(2);
    }else if(k<1&&k>-1&&event->position().x()<clickPoint.x()){
        qDebug()<<"got to left";
        emit goTo(3);
    }
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

void GameScreen::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"release up";
        emit goTo(0);
        break;
    case Qt::Key_Down:
        qDebug()<<"release down";
        emit goTo(2);
        break;
    case Qt::Key_Left:
        qDebug()<<"release left";
        emit goTo(3);
        break;
    case Qt::Key_Right:
        qDebug()<<"release right";
        emit goTo(1);
        break;
    default:
        break;
    }
}

void GameScreen::initalScreen()
{
    setFixedSize(500,500);
    view->resize(500,500);
    view->setWindowTitle("Snake");
    view->setBackgroundBrush(QBrush(qRgb(238,232,170)));
    for(int i=150;i<475;i=i+100){
        group->addToGroup(new QGraphicsLineItem(i,50,i,450));
    }
    for(int i=150;i<475;i=i+100){
        group->addToGroup(new QGraphicsLineItem(50,i,450,i));
    }
    QGraphicsRectItem* rect=new QGraphicsRectItem(50,50,400,400);
    group->addToGroup(rect);
    scene->addItem(group);
}

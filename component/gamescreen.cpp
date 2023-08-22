#include "gamescreen.h"
#include <QMouseEvent>

gameScreen::gameScreen(QWidget* parent)
    : QWidget(parent)
{
    initalScreen();
}

gameScreen::~gameScreen()
{
    ;
}

void gameScreen::setGame(QWidget* game)
{
    layout->addWidget(game);
}

void gameScreen::mousePressEvent(QMouseEvent* event)
{
    qDebug()<<"Mouse : press on "<<event->position();
    clickPoint.rx()=event->position().x();
    clickPoint.ry()=event->position().y();
    grabMouse();
    clicked(clickPoint);
}

void gameScreen::mouseReleaseEvent(QMouseEvent *event)
{
    releaseMouse();
    qDebug()<<"Mouse : release on the "<<event->position();
    double k=(event->position().y()-clickPoint.y())/(event->position().x()-clickPoint.x());
    if((k>1||k<-1)&&event->position().y()<clickPoint.y()){
        qDebug()<<"Mouse : go to front";
        emit moveTo(directionOfFront);
    }else if(k<1&&k>-1&&event->position().x()>clickPoint.x()){
        qDebug()<<"Mouse : go to right";
        emit moveTo(directionOfRight);
    }else if((k>1||k<-1)&&event->position().y()>clickPoint.y()){
        qDebug()<<"Mouse : go to behind";
        emit moveTo(directionOfBehind);
    }else if(k<1&&k>-1&&event->position().x()<clickPoint.x()){
        qDebug()<<"Mouse : go to left";
        emit moveTo(directionOfLeft);
    }
}

void gameScreen::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"KeyBorad : press up";
        emit moveTo(directionOfFront);
        break;
    case Qt::Key_Down:
        qDebug()<<"KeyBorad : press down";
        emit moveTo(directionOfBehind);
        break;
    case Qt::Key_Left:
        qDebug()<<"KeyBorad : press left";
        emit moveTo(directionOfLeft);
        break;
    case Qt::Key_Right:
        qDebug()<<"KeyBorad : press right";
        emit moveTo(directionOfRight);
        break;
    default:
        break;
    }
}

void gameScreen::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"KeyBorad : release up";
        emit moveTo(directionOfFront);
        break;
    case Qt::Key_Down:
        qDebug()<<"KeyBorad : release down";
        emit moveTo(directionOfBehind);
        break;
    case Qt::Key_Left:
        qDebug()<<"KeyBorad : release left";
        emit moveTo(directionOfLeft);
        break;
    case Qt::Key_Right:
        qDebug()<<"KeyBorad : release right";
        emit moveTo(directionOfRight);
        break;
    default:
        break;
    }
}

void gameScreen::initalScreen()
{
    resize(500,500);
    layout=new QHBoxLayout(this);
}
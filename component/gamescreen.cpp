#include "gamescreen.h"
#include <QMouseEvent>
#include <QDebug>

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
    #if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
        qDebug()<<"Mouse : press on "<<event->pos();
        clickPoint.rx()=event->pos().x();
        clickPoint.ry()=event->pos().y();
    #elif (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        qDebug()<<"Mouse : press on "<<event->position();
        clickPoint.rx()=event->position().x();
        clickPoint.ry()=event->position().y();
    #endif
    emit clicked(clickPoint);
    grabMouse();
}

void gameScreen::mouseReleaseEvent(QMouseEvent *event)
{
    releaseMouse();
    #if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
        qDebug()<<"Mouse : release on the "<<event->pos();
        qreal x=event->pos().x()-clickPoint.x();
        qreal y=event->pos().y()-clickPoint.y();
        double k=(x!=0)?y/x:0;
        if((k>1||k<-1)&&event->pos().y()<clickPoint.y()){
            qDebug()<<"Mouse : go to front";
            emit moveTo(directionOfFront);
        }else if(k<1&&k>-1&&event->pos().x()>clickPoint.x()){
            qDebug()<<"Mouse : go to right";
            emit moveTo(directionOfRight);
        }else if((k>1||k<-1)&&event->pos().y()>clickPoint.y()){
            qDebug()<<"Mouse : go to behind";
            emit moveTo(directionOfBehind);
        }else if(k<1&&k>-1&&event->pos().x()<clickPoint.x()){
            qDebug()<<"Mouse : go to left";
            emit moveTo(directionOfLeft);
        }
    #elif (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
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
    #endif
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
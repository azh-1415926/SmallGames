#include "gamescreen.h"
#include <QMouseEvent>
#include <QDebug>

gameScreen::gameScreen(QWidget* parent)
    : QWidget(parent)
{
    /* 初始化游戏屏幕 */
    initalScreen();
}

gameScreen::~gameScreen()
{
    ;
}

/* 设置游戏窗口 */
void gameScreen::setGame(QWidget* game)
{
    this->game=game;
    layout->addWidget(game);
}

/* 初始化屏幕 */
void gameScreen::initalScreen()
{
    /* 调整窗口大小、设置垂直布局为整体布局 */
    resize(500,500);
    layout=new QHBoxLayout(this);
    game=nullptr;
}

/* 重写鼠标点击事件，发送 clicked(const QPoint&)信号 */
void gameScreen::mousePressEvent(QMouseEvent* event)
{
    #if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
        clickPoint.rx()=event->pos().x();
        clickPoint.ry()=event->pos().y();
    #elif (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        clickPoint.rx()=event->position().x();
        clickPoint.ry()=event->position().y();
    #endif
    /* 设置为相对位置 */
    qDebug()<<"game pos: "<<game->geometry();
    if(game!=nullptr){
        clickPoint.rx()-=game->geometry().x();
        clickPoint.ry()-=game->geometry().y();
    }
    qDebug()<<"Mouse : press on "<<clickPoint;
    emit clicked(clickPoint);
    grabMouse();
}

/* 重写鼠标点释放事件，计算鼠标点击和释放的偏移方向，发送 moveTo(enum moveDirection)信号 */
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

/* 重写键盘点击事件，发送 moveTo(enum moveDirection)信号 */
void gameScreen::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        qDebug()<<"KeyBorad : press up";
        break;
    case Qt::Key_Down:
        qDebug()<<"KeyBorad : press down";
        break;
    case Qt::Key_Left:
        qDebug()<<"KeyBorad : press left";
        break;
    case Qt::Key_Right:
        qDebug()<<"KeyBorad : press right";
        break;
    default:
        break;
    }
}

/* 重写键盘释放事件 */
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

/* 重写窗口关闭事件，发送 closed()信号 */
void gameScreen::closeEvent(QCloseEvent *e)
{
    emit closed();
}
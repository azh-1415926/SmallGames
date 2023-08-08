#include "chessboard.h"
#include <QMouseEvent>

ChessBoard::ChessBoard(QWidget* parent)
    : QWidget(parent)
    , boardScene(new QGraphicsScene(this))
    , widgetView(new QGraphicsView(boardScene,this))
    , currColor(qRgb(255,222,173))
{
    widgetView->setWindowTitle("Three Chess");
    widgetView->resize(500,500);
    widgetView->setBackgroundBrush(QBrush(QColor(qRgb(255,222,173))));
    for(int i=0;i<9;i++)
        chequers<<nullptr;
    initalBoard();
}

void ChessBoard::showBoard()
{
    if(currColor!=qRgb(255,222,173)){
        clearBoard();
    }
    currColor=qRgb(255,222,173);
    show();
    emit clickBoard(-1);
}
void ChessBoard::clearBoard(){
    for(int i=0;i<9;i++){
        if(chequers[i]!=nullptr){
            delete chequers[i];
            chequers[i]=nullptr;
        }
    }
}
void ChessBoard::addChequer(int pos, const QColor &color)
{
    if(currColor==color){
        return;
    }else if(chequers[pos]!=nullptr){
        emit clickBoard(-1);
    }else{
        currColor=color;
        setChequer(pos);
    }
}
void ChessBoard::initalBoard()
{
    QPen pen(Qt::DotLine);
    QGraphicsItemGroup *group=new QGraphicsItemGroup;
    QGraphicsLineItem* line=new QGraphicsLineItem(100,200,400,200);
    line->setPen(pen);
    group->addToGroup(line);
    line=new QGraphicsLineItem(100,300,400,300);
    line->setPen(pen);
    group->addToGroup(line);
    line=new QGraphicsLineItem(200,100,200,400);
    line->setPen(pen);
    group->addToGroup(line);
    line=new QGraphicsLineItem(300,100,300,400);
    line->setPen(pen);
    group->addToGroup(line);
    group->addToGroup(new QGraphicsRectItem(100,100,300,300));
    boardScene->addItem(group);
}
void ChessBoard::setChequer(int pos)
{
    int row=pos/3;
    int column=pos%3;
    chequers[pos]=new QGraphicsEllipseItem;
    chequers[pos]->setRect(115+column*100,115+row*100,70,70);
    chequers[pos]->setBrush(QBrush(currColor));
    boardScene->addItem(chequers[pos]);
    emit setSuccess();
    if(isWin(pos)){
        emit settleGame(" is wins!");
    }else{
        for(int i=0;i<9;i++){
            if(chequers[i]==nullptr){
                break;
            }
            if(i==8){
                emit settleGame(",no one wins");
            }
        }
    }
    emit clickBoard(-1);
}
int ChessBoard::playerAction(int x, int y)
{
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
bool ChessBoard::isWin(int pos)
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
void ChessBoard::mousePressEvent(QMouseEvent* event)
{
    int pos=playerAction(event->position().x(),event->position().y());
    if(pos!=-1){
        emit clickBoard(pos);
    }
}

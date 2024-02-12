#include "gameview.h"
#include "constants.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

gameView::gameView(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene))
    , group(new QGraphicsItemGroup)
    , flagOfGame(0)
    , colorOfChequer(Qt::black,Qt::white)
{
    /* 初始化游戏窗口的界面、游戏互动部分 */
    initalView();
    initalGame();
}

gameView::~gameView()
{
    /* 释放各个组件 */
    delete scene;
    delete view;
    delete group;
}

/* 初始化游戏 */
void gameView::startGame()
{
    /* 若游戏标志位为 1，则执行清理操作 */
    if(flagOfGame==1)
        clearView();
    /* 游戏初始化，玩家选择棋子样式和先手玩家 */
    int option=-1;
    if(flagOfGame==0){
        option=QMessageBox::question(nullptr,"Game Initalize...","choose your chequer!","black chequer","white chequer");
        colorOfChequer.first=option?Qt::white:Qt::black;
        colorOfChequer.second=option?Qt::black:Qt::white;
        option=QMessageBox::question(NULL,"Game Initalize...","choose the first player!","your","computer");
        currColor=option?colorOfChequer.second:colorOfChequer.first;
    }
    /* 游戏开始，flagOfGame 置为 1，记录开始时间 */
    flagOfGame=1;
    startTime=clock();
    /* 只有当电脑先手时才能有效执行 */
    addChequer(-1);
}

/* 清理游戏 */
void gameView::clearView(){
    /* 清理屏幕上所有的棋子 */
    for(int i=0;i<225;i++){
        if(chequers[i]!=nullptr){
            delete chequers[i];
            chequers[i]=nullptr;
        }
    }
    /* 游戏标志位置为 0，代表着游戏未初始化(游戏结束) */
    flagOfGame=0;
}

/* 处理玩家点击操作 */
void gameView::clickPoint(const QPoint &p)
{
    /* 若未命中棋盘上的所有位置，返回 -1，直接返回 */
    int pos=getPlayerOptionByPoint(p);
    if(pos==-1)
        return;
    /* 在 pos 处添加棋子，若当前不为玩家回合，此时添加棋子无效 */
    addChequer(pos);
}

/* 重试(电脑行动) */
void gameView::doComputer()
{
    /* 只有当此处回合为电脑才可进行重试 */
    if(currColor==colorOfChequer.second)
        addChequer(-1);
}

/* 初始化游戏界面 */
void gameView::initalView()
{
    /* 选用垂直布局作为游戏窗口的整体布局 */
    QHBoxLayout* layout=new QHBoxLayout(this);
    /* 设置 view 的大小、背景颜色、并添加到布局中 */
    view->resize(500,500);
    view->setBackgroundBrush(QBrush(QColor(qRgb(255,222,173))));
    layout->addWidget(view);
    /* pen 设置为虚线，并用 line 来临时存储线条指针 */
    QPen pen(Qt::DotLine);
    QGraphicsLineItem* line=nullptr;
    /* 指定范围画上网格，矩形范围在 constants.h 文件里 */
    const QRect& range=RANGE;
    /* 线条之间的间隔 */
    qreal gapOfX=GAPOFX;
    qreal gapOfY=GAPOFY;
    /* 添加一个矩形到 group 中 */
    group->addToGroup(new QGraphicsRectItem(range));
    /* 在矩形范围内添加线条 */
    qreal x=range.x()+gapOfX;
    qreal y=range.y()+gapOfY;
        for(;x<range.x()+range.width()&&y<range.y()+range.height();x+=gapOfX,y+=gapOfY){
            /* 添加纵向的线条，其横坐标不变，并添加到 group 中 */
            line=new QGraphicsLineItem(range.x(),y,range.x()+range.width(),y);
            line->setPen(pen);
            group->addToGroup(line);
            /* 添加横向的线条，其纵坐标不变，并添加到 group 中 */
            line=new QGraphicsLineItem(x,range.y(),x,range.y()+range.height());
            line->setPen(pen);
            group->addToGroup(line);
        }
    /* 将 group 添加到 scene 中 */
    scene->addItem(group);
}

/* 初始化游戏 */
void gameView::initalGame()
{
    /* 初始化随机数种子*/
    srand(time(NULL));
    /* 初始化屏幕上的棋子，默认为 nullptr */
    for(int i=0;i<225;i++)
        chequers<<nullptr;
}

/* 结算游戏 */
void gameView::settleGame(const QString &tip)
{
    /* player 为此次获胜的玩家名称，若无人获胜，置为 "" */
    QString player=(currColor==colorOfChequer.first)?("player"):("computer");
    if(tip=="no one wins")
        player="";
    /* 结算玩家名称、时间 */
    emit settlePlayer(player);
    emit settleTime((clock()-startTime)/1000.0);
    /* 获取玩家选择的结果 */
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!",player+tip+",do you want to play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    /* 若为 Ok，则再次游戏，即调用 startGame()，用于初始化新的一次游戏，并返回 */
    if(result==QMessageBox::Ok){
        /* 执行清理操作，并再次初始化游戏 */
        clearView();
        startGame();
        return;
    }
    /* 否则发送 closeGame()信号，外部接收到该信号会自动关闭游戏屏幕并调用 clearView() */
    emit closeGame();
}

/* 当前玩家在指定位置添加棋子 */
void gameView::addChequer(int pos)
{
    /* 若游戏未初始化，直接返回 */
    if(flagOfGame==0){
        qDebug()<<"Game is not initalize";
        return;
    }
    /* 若当前回合为电脑，指定的 pos 无效，将自动获取选项 */
    if(currColor==colorOfChequer.second){
        pos=getComputerOption();
        qDebug()<<"getComputerOption:"<<pos;
    }else if(currColor==colorOfChequer.first&&pos!=-1){
        /* 若当前回合为玩家，指定的 pos 不能为 -1，将不执行下棋操作 */
        qDebug()<<"getPlayerOption:"<<pos;
    }
    /* 若落棋位置处已有棋子 */
    if(pos==-1||chequers[pos]!=nullptr){
        /* 若此回合为电脑 */
        if(currColor==colorOfChequer.second){
            /* 查找棋盘上是否还有空位，若无返回 -1 */
            pos=chequers.indexOf(nullptr);
            /* 若有空位，理应让电脑再次尝试 */
            if(pos!=-1)
                doComputer();
        }
        /* 若此回合为玩家，直接返回就好 */
        return;
    }
    /* 在指定位置落棋 */
    setChequer(pos);
}

/* 指定位置落下当前回合棋子 */
void gameView::setChequer(int pos)
{
    /* 获取 pos 的行列信息 */
    int row=pos/15;
    int column=pos%15;
    /* 棋子为圆形，半径为颜色方块的 7/10，在格子边距的 3/20 像素位置落棋 */
    chequers[pos]=new QGraphicsEllipseItem;
    chequers[pos]->setRect(RANGE.x()+GAPOFX*3/20+column*GAPOFX,RANGE.y()+GAPOFY*3/20+row*GAPOFY,GAPOFX*7/10,GAPOFY*7/10);
    /* 设置棋子颜色，并落棋 */
    chequers[pos]->setBrush(QBrush(currColor));
    scene->addItem(chequers[pos]);
    /* 判断当前落棋操作是否会引起游戏胜利 */
    if(isWin(pos)){
        /* 若胜利，则结算游戏 */
        settleGame(" is wins");
        return;
    }else{
        /* 若未胜利，则查找棋盘山是否有空位 */
        pos=chequers.indexOf(nullptr);
        /* 若无空位，理应结算游戏 */
        if(pos==-1){
            settleGame("no one wins");
            return;
        }
    }
    /* 切换到下个玩家，即下一回合 */
    switchNextPlayer();
    /* 若当前回合为电脑回合，则电脑落棋 */
    if(currColor==colorOfChequer.second)
        doComputer();
}

/* 切换玩家，即切换回合 */
void gameView::switchNextPlayer()
{
    qDebug()<<"Switch to "<<(currColor==colorOfChequer.first?"player":"computer");
    currColor=(currColor==colorOfChequer.first?colorOfChequer.second:colorOfChequer.first);
}

/* 获取电脑落棋位置 */
int gameView::getComputerOption(){
    return rand()%225;
}

/* 根据玩家点击坐标获取玩家落棋位置 */
int gameView::getPlayerOptionByPoint(const QPoint& p)
{
    /* 获取 group 在屏幕上的真实坐标(base)，当窗口拉伸，base 也会变化 */
    const QPointF& base=view->mapFromScene(group->scenePos())+view->pos();
    /* 引用 constants.h 里的矩形范围 RANGE */
    const QRect& range=RANGE;
    /* 以 baseOfX 和 baseOfY 作为棋盘的最小范围 */
    qreal baseOfX=range.x();
    qreal baseOfY=range.y();
    /* 以 topOfX 和 topOfY 作为棋盘的最大范围 */
    qreal topOfX=range.x()+range.width();
    qreal topOfY=range.y()+range.height();
    /* x、y 为坐标 p 相对于 group 的相对坐标值 */
    qreal x=p.x()-base.x();
    qreal y=p.y()-base.y();
    /* 当相对坐标 x、y 超出棋盘范围，或小于棋盘的最小范围，则表明 p 点坐标无效，直接返回 */
    if(x<=baseOfX||x>=topOfX||y<=baseOfY||y>=topOfY)
        return -1;
    /* i 为在棋盘落棋的行数，相对坐标值-棋盘最小范围，然后 / y 轴方向上棋盘的间隔 */
    int i=(y-baseOfY)/GAPOFY;
    /* j 为在棋盘落棋的列数，相对坐标值-棋盘最小范围，然后 / x 轴方向上棋盘的间隔 */
    int j=(x-baseOfX)/GAPOFX;
    /* 得出棋盘行数和列数 i、j 后，计算下标，为行数*(棋盘线条数+1)+列数 */
    return i*(NX+1)+j;
}

/* 判断某位置落棋是否会导致游戏胜利 */
bool gameView::isWin(int pos)
{
    int _row=15,_column=15;
    int _linkedCount=5;
    /* row、column 为计算出的行号和列号，count 为连珠数，maxcount 为最大连珠数 */
    int row=pos/_column;
    int column=pos%_column;
    int count=1;
    int flag=1;
    int rflag=1;
    const QColor& color=chequers[pos]->brush().color();
    //horizon
    for(int i=1;i<_linkedCount;++i){
        if(flag&&column+i<_column){
            if(chequers[row*_column+column+i]==nullptr)
                break;
            if(color==chequers[row*_column+column+i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&column-i>=0){
            if(chequers[row*_column+column-i]==nullptr)
                break;
            if(color==chequers[row*_column+column-i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount)
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //vertical
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row+i<_row){
            if(chequers[(row+i)*_column+column]&&color==chequers[(row+i)*_column+column]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0){
            if(chequers[(row-i)*_column+column]&&color==chequers[(row-i)*_column+column]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount)
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row+i<_row&&column+i<_column){
            if(chequers[(row+i)*_column+column+i]&&color==chequers[(row+i)*_column+column+i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0&&column-i>=0){
            if(chequers[(row-i)*_column+column-i]&&color==chequers[(row-i)*_column+column-i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount)
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row-i>=0&&column+i<_column){
            if(chequers[(row-i)*_column+column+i]&&color==chequers[(row-i)*_column+column+i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row+i<_row&&column-i>=0){
            if(chequers[(row+i)*_column+column-i]&&color==chequers[(row+i)*_column+column-i]->brush().color()){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount)
        return true;
    return false;
}
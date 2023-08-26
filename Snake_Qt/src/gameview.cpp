#include "gameview.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

gameView::gameView(QWidget* parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView(scene))
    , group(new QGraphicsItemGroup)
    , flagOfGame(0)
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

/* 重写计时器事件，定时移动蛇身，且重置 flagOfTime 为 0 */
void gameView::timerEvent(QTimerEvent *e)
{
    moving(lastDirection);
    flagOfTime=0;
}

/* 初始化游戏 */
void gameView::startGame()
{
    /* 若游戏标志位为 1，则执行清理操作 */
    if(flagOfGame==1)
        clearView();
    /* 游戏开始，更新游戏开始时间、启动计时器用于重置 flagOfTime、将 flagOfGame 置为 1，将 flagOfTime 置为 0 */
    startTime=clock();
    timerId=startTimer(1000);
    flagOfGame=1;
    flagOfTime=0;
    /* 设置上一次的移动方向为 0(向前)、设置蛇头蛇尾的下标、将 food 置空 */
    lastDirection=0;
    head=tail=40;
    food=nullptr;
    /* 更新蛇头位置的方块、并添加食物 */
    updateBlock(head);
    addFood();
}

/* 清理游戏 */
void gameView::clearView()
{
    /* 关闭定时器 */
    killTimer(timerId);
    /* 清理屏幕上的蛇身 */
    for(int i=0;i<81;i++){
        if(blocks[i]!=nullptr){
            delete blocks[i];
            blocks[i]=nullptr;
        }
    }
    /* 将蛇身坐标清空 */
    snake.clear();
    /* food 置空，因为 food 指向 blocks 里的一个元素，上面已经清空了 */
    food=nullptr;
    /* 游戏标志位置为 0，代表着游戏未初始化(游戏结束) */
    flagOfGame=0;
}

/* 处理玩家移动操作 */
void gameView::moveTo(int direction)
{
    /* 游戏标志位为 0(未初始化游戏)，时间标志位为 1(1 秒内已进行过操作)，则返回 */
    if(flagOfGame==0||flagOfTime==1)
        return;
    /* 立即将 flagOfTime 置为 1，一秒后自动被定时器事件置为 0 */
    flagOfTime=1;
    /* 计算出合法的方向，例如当蛇头往前移动的时候，不能往后移动 */
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

/* 初始化游戏界面 */
void gameView::initalView()
{
    /* 选用垂直布局作为游戏窗口的整体布局 */
    QHBoxLayout* layout=new QHBoxLayout(this);
    /* 设置 view 的大小、背景颜色、并添加到布局中 */
    view->resize(500,500);
    view->setBackgroundBrush(QBrush(qRgb(107,142,35)));
    layout->addWidget(view);
    /* 指定范围画上网格，矩形范围为 (25,25,450,450) */
    QRect range(25,25,450,450);
    QGraphicsLineItem* line=nullptr;
    /* 设置线条的数量 n */
    qreal n=8.0;
    /* 线条之间的间隔 */
    qreal gapOfX=range.width()/(n+1);
    qreal gapOfY=range.height()/(n+1);
    /* 添加一个矩形到 group 中 */
    group->addToGroup(new QGraphicsRectItem(range));
    /* 在矩形范围内添加线条 */
    qreal x=range.x()+gapOfX;
    qreal y=range.y()+gapOfY;
    for(;x<range.x()+range.width()&&y<range.y()+range.height();x+=gapOfX,y+=gapOfY){
        /* 添加纵向的线条，其横坐标不变，并添加到 group 中 */
        line=new QGraphicsLineItem(range.x(),y,range.x()+range.width(),y);
        group->addToGroup(line);
        /* 添加横向的线条，其纵坐标不变，并添加到 group 中 */
        line=new QGraphicsLineItem(x,range.y(),x,range.y()+range.height());
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
    /* 初始化屏幕上网格里的方块，默认为 nullptr */
    for(int i=0;i<81;i++)
        blocks<<nullptr;
}

/* 结算游戏 */
void gameView::settleGame()
{
    /* 结算时间、长度 */
    emit settleTime((clock()-startTime)/1000.0);
    emit settleLength(snake.length());
    /* 获取玩家选择的结果 */
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!","Do you want play again?",QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
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

/* 移动蛇身到指定方向 */
void gameView::moving(int direction)
{
    /* p 用于存储蛇头坐标 */
    static QPoint p;
    /* 存储当前蛇头坐标 */
    p.rx()=25+head%9*50;
    p.ry()=25+head/9*50;
    /* 计算出新蛇头的位置 */
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
    /* 将新蛇头的位置入队、更新蛇头 */
    snake.enqueue(p);
    updateHead(p);
}

/* 更新蛇头 */
void gameView::updateHead(const QPoint& head)
{
    /* 若蛇头撞墙，则结算游戏并返回 */
    qDebug()<<"try to mouse head to "<<head;
    if(head.x()<25||head.x()>425||head.y()<25||head.y()>425){
        qDebug()<<"head error";
        settleGame();
        return;
    }
    /* 计算出蛇头坐标对应的下标 pos */
    int pos=(head.x()-25)/50+(head.y()-25)/50*9;
    qDebug()<<"head pos:"<<pos;
    /* 若当前蛇头位置是 food，则将 food 的笔刷置为蛇头的颜色(黄色)，并将 food 置空 */
    if(blocks[pos]==food){
        food->setBrush(Qt::yellow);
        food=nullptr;
    }
    /* 更新 pos 位置的方块，若更新位置有蛇身，即该位置的方块不为空且 food 也不为空，就会将 flagOfGame 置为 0 */
    updateBlock(pos);
    /* 若 flagOfGame 为 0，即碰撞了蛇身，则结算游戏 */
    if(flagOfGame==0){
        settleGame();
        return;
    }
    /* 若 food 为空，则调用 addFood()，即重新添加新的 food，否则更新蛇尾 */
    if(food==nullptr)
        addFood();
    else
        updateTail(snake.dequeue());
    this->head=pos;
}

/* 更新蛇尾 */
void gameView::updateTail(const QPoint& tail)
{
    /* 若蛇尾撞墙，则结算游戏并返回，一般情况不会触发 */
    qDebug()<<"try to mouse tail to "<<tail;
    if(tail.x()<25||tail.x()>425||tail.y()<25||tail.y()>425){
        qDebug()<<"tail error";
        return;
    }
    /* 清除旧蛇尾处的方块、并计算出新蛇尾的下标，记录下来 */
    clearBlock(this->tail);
    this->tail=(tail.x()-25)/50+(tail.y()-25)/50*9;
}

/* 更新指定方块 */
void gameView::updateBlock(int pos)
{
    int row=pos/9;
    int column=pos%9;
    /* 若该位置的方块为空，才创建新的方块，并设置笔刷颜色，添加到 group 中 */
    if(blocks[pos]==nullptr){
        blocks[pos]=new QGraphicsRectItem(25+column*50,25+row*50,50,50);
        blocks[pos]->setBrush(QBrush(Qt::yellow));
        group->addToGroup(blocks[pos]);
    /* 若该处方块既不为空，而且 food 也不为空，即碰撞了蛇身，将 flagOfGame 置为 0 */
    }else if(food!=nullptr){
        flagOfGame=0;
    }
}

/* 清除指定方块 */
void gameView::clearBlock(int pos)
{
    /* 释放指定位置的方块，并将该指针置空 */
    if(blocks[pos]!=nullptr){
        delete blocks[pos];
        blocks[pos]=nullptr;
    }
}

/* 添加食物 */
void gameView::addFood()
{
    /* pos 为随机出的下标，用于放置 food */
    int pos=-1;
    while(pos==-1||blocks[pos]!=nullptr){
        pos=rand()%81;
        /* 若屏幕上被占满，则返回 */
        if(blocks.indexOf(nullptr)==-1)
            return;
    }
    /* 在 pos 位置添加方块，食物笔刷颜色为灰色，并添加到 group 中 */
    blocks[pos]=new QGraphicsRectItem(25+pos%9*50,25+pos/9*50,50,50);
    blocks[pos]->setBrush(Qt::gray);
    group->addToGroup(blocks[pos]);
    /* 用 food 指向该方块 */
    food=blocks[pos];
}
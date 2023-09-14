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

/* 重写 timerEvent,重置 flagOfTime 为 0 */
void gameView::timerEvent(QTimerEvent *event)
{
    flagOfTime=0;
}

/* 初始化游戏 */
void gameView::startGame()
{
    /* 若游戏标志(flagOfGame)为 1，代表游戏已开始，意味着上一次的游戏未清理，执行清理函数 */
    if(flagOfGame==1)
        clearView();
    /* 游戏开始，更新游戏开始时间、启动计时器用于重置 flagOfTime、将 flagOfGame 置为 1，将 flagOfTime 置为 0 */
    startTime=clock();
    timerId=startTimer(250);
    flagOfGame=1;
    flagOfTime=0;
    /* 清空用于计算数字合成结果的数组 */
    memset(array,0,sizeof(array));
    /* 初始化当前最大数为 0，空位有 16 个，并添加一个数字到屏幕上 */
    maxNumber=0;
    zeroCount=16;
    score=0;
    addNumber();
}

/* 执行清理工作 */
void gameView::clearView()
{
    /* 结束定时器的运行、将屏幕上所有数字清零 */
    killTimer(timerId);
    /* 清空屏幕上的颜色方块、数组文本 */
    for(int i=0;i<16;i++)
    {
        if(blocks[i]!=nullptr)
        {
            delete blocks[i];
            blocks[i]=nullptr;
            numbers[i]->setPlainText("");
        }
    }
    /* flagOfGame 置为 0，意味着游戏未开始 */
    flagOfGame=0;
}

/* 处理玩家的移动操作 */
void gameView::moveTo(int direction)
{
    /* 当 flagOfTime 为 1，则直接返回(相当于冷却时间)，反之则立即置为 1 */
    if(flagOfTime==1)
        return;
    flagOfTime=1;
    /* 用 preDirection 记录上一次的移动方向 */
    static int preDirection;
    /* 为相应的移动方向计算移动后的数字 */
    switch(direction)
    {
    case 0:
        moveFront();
        qDebug()<<"move front";
        break;
    case 1:
        moveRight();
        qDebug()<<"move right";
        break;
    case 2:
        moveBehind();
        qDebug()<<"move behind";
        break;
    case 3:
        moveLeft();
        qDebug()<<"move left";
        break;
    }
    /* 若屏幕上仅存在一个数字或当前移动方向与上次不相同才可添加新的数字，并更新新的 preDirection */
    if(zeroCount>=15||preDirection!=direction)
        addNumber();
    preDirection=direction;
    /* 打印计移动后的数字数组 */
    qDebug()<<"----gameInfo----";
    for(int i=0;i<4;i++){
        qDebug()<<"|"<<array[i][0]<<"|"<<array[i][1]<<"|"<<array[i][2]<<"|"<<array[i][3]<<"|";
    }
    qDebug()<<"----------------";
    /* 若当前最大数字超过 2048或屏幕上已被数字占满，则试图结算游戏 */
    if(maxNumber>=2048||zeroCount==0)
        settleGame();
}

/* 初始化游戏界面 */
void gameView::initalView()
{
    /* 选用垂直布局作为游戏窗口的整体布局 */
    QHBoxLayout* layout=new QHBoxLayout(this);
    /* 设置背景色，并添加到布局中 */
    view->setBackgroundBrush(QBrush(qRgb(238,232,170)));
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
    for(;x<range.x()+range.width()&&y<range.y()+range.height();x+=gapOfX,y+=gapOfY)
    {
        /* 添加纵向的线条，其横坐标不变，设置线条的 QPen，并添加到 group 中 */
        line=new QGraphicsLineItem(range.x(),y,range.x()+range.width(),y);
        line->setPen(pen);
        group->addToGroup(line);
        /* 添加横向的线条，其纵坐标不变，设置线条的 QPen，并添加到 group 中 */
        line=new QGraphicsLineItem(x,range.y(),x,range.y()+range.height());
        line->setPen(pen);
        group->addToGroup(line);
    }
    /* 将 group 添加到 scene 中 */
    scene->addItem(group);
}

/* 初始化游戏模块 */
void gameView::initalGame()
{
    /* 初始化随机数种子*/
    srand(time(NULL));
    /* 初始化 4x4 网格上的方块显示、数字显示 */
    QFont font;
    font.setPointSize((GAPOFX+GAPOFY)/2/4);
    for(int i=0;i<16;i++)
    {
        /* blocks 数组存储着屏幕上显示数字颜色的方块的 QGraphicsRectItem* 指针，无方块为 nullptr */
        blocks<<nullptr;
        /* numbers 数组存储着屏幕上显示数字的 QGraphicsTextItem* 指针，无数字，文本内容为 "" */
        numbers<<new QGraphicsTextItem;
        /* 设置所显示数字的字体、坐标、放置优先级(默认为 0，即按放置顺序的先后覆盖，设置为 1，避免被颜色方块遮挡) */
        numbers[i]->setFont(font);
        numbers[i]->setPos(RANGE.x()+i%4*GAPOFX,RANGE.y()+GAPOFY/4+i/4*GAPOFY);
        numbers[i]->setZValue(1);
        /* 由于当前没有颜色方块，故只需要将显示数字的文本添加到 group 中 */
        group->addToGroup(numbers[i]);
    }
}

/* 结算游戏 */
void gameView::settleGame()
{
    /* 若屏幕被数字占满才会触发结算游戏，若最大数不为 2048，便要执行 isOver()，判断游戏是否彻底结束，否则直接返回，继续游戏 */
    if(maxNumber<2048&&!isOver())
        return;
    /* 提示窗口的文本内容，根据游戏是否胜利设置文本 */
    QString tip;
    if(maxNumber>=2048)
        tip.append("You win ! Do you want play again?");
    else if(zeroCount==0)
        tip.append("You failed ! Do you want play again?");
    /* 结算游戏时间、分数 */
    emit settleTime((clock()-startTime)/1000.0);
    emit settleScore(score);
    /* 获取玩家选择的结果 */
    QMessageBox::Button result=QMessageBox::question(nullptr,"Game Over!",tip,QMessageBox::Ok|QMessageBox::No,QMessageBox::No);
    /* 若为 Ok，则再次游戏，即调用 startGame()，用于初始化新的一次游戏 */
    if(result==QMessageBox::Ok)
        startGame();
    /* 否则执行清理操作、并发送 closeGame()信号 */
    else
    {
        clearView();
        emit closeGame();
    }
}

/* 往屏幕上添加数字 */
void gameView::addNumber()
{
    /* pos 为数字放置的坐标，num 为随机的数字，应为 2、4 中的一个数字 */
    int pos=-1;
    int num=-1;
    /* 若随机到的 pos 位置上已有数字，则再次随机生成一个 pos */
    while(pos==-1||pos!=-1&&array[pos/4][pos%4]!=0)
    {
        pos=rand()%16;
        /* 若屏幕已被占满则返回 */
        if(zeroCount==0)
            return;
    }
    /* num 随机到 2 的余数(0、1)并加一(1、2)，再乘上 2(2、4)，刚好符合要求 */
    num=(rand()%2+1)*2;
    /* 将 num 放置到 pos 位置上，并更新该位置上的颜色方块和数字文本，屏幕上空位减一 */
    array[pos/4][pos%4]=num;
    updatePoint(pos,num);
    zeroCount--;
}

/* 更新指定位置上的颜色方块及数字文本 */
void gameView::updatePoint(int pos,int num)
{
    /* 若颜色方块为空，则创建一个新的，并将其添加到 group 中 */
    if(blocks[pos]==nullptr)
    {
        blocks[pos]=new QGraphicsRectItem(RANGE.x()+pos%4*GAPOFX,RANGE.y()+pos/4*GAPOFY,GAPOFX,GAPOFY);
        group->addToGroup(blocks[pos]);
    }
    /* str 为数字文本内容 */
    QString str=QString::number(num);
    /*
        offset 为数字文本的 x 坐标偏移量，用于对齐数字
        由于方块内只能容纳 4 位数字(总共 100 像素)，而数字文本也在 1-4 位之间
        而减去当前数字的长度并 /2.0(保留小数)再 * 1 位数字的大小(1位便是 25)就能得出合适的偏移量大小
    */
    qreal offset=(4-str.length())/2.0*GAPOFX/4;
    /* 设置数字的文本、坐标，设置颜色方块的笔刷(更新颜色) */
    numbers[pos]->setPlainText(str);
    numbers[pos]->setPos(RANGE.x()+pos%4*GAPOFX+offset,RANGE.y()+GAPOFY/4+pos/4*GAPOFY);
    blocks[pos]->setBrush(getBrushByNum(num));
}

/* 清除指定位置上的颜色方块、数字文本 */
void gameView::clearPoint(int pos)
{
    /* 若该位置上的颜色方块不为空，才释放并将该指针置空，且将数字文本清空 */
    if(blocks[pos]!=nullptr)
    {
        delete blocks[pos];
        blocks[pos]=nullptr;
        numbers[pos]->setPlainText("");
    }
}

/* 更新分数，传入合成后的数字 */
void gameView::updateScore(int num)
{
    /* 与当前最大数字进行比较，若传入数字更大，则更新最大数字 */
    if(num>maxNumber)
        maxNumber=num;
    /* 总分直接加 num，即合成的数字就是所得分，由于合成数字必会有一个空位，故屏幕空位加一 */
    score+=num;
    zeroCount++;
}

/* 获取指定数字的颜色笔刷 */
QBrush gameView::getBrushByNum(int i)
{
    switch (i)
    {
    case 2:
        //玉米丝
        return QBrush(qRgb(255,248,220));
        break;
    case 4:
        //杏仁变白
        return QBrush(qRgb(255,235,205));
        break;
    case 8:
        //浓汤
        return QBrush(qRgb(255,228,196));
        break;
    case 16:
        //小麦
        return QBrush(qRgb(245,222,179));
        break;
    case 32:
        //棕褐色
        return QBrush(qRgb(210,180,140));
        break;
    case 64:
        //魁梧的木头
        return QBrush(qRgb(222,184,135));
        break;
    case 128:
        //沙棕色
        return QBrush(qRgb(244,164,96));
        break;
    case 256:
        //秘鲁
        return QBrush(qRgb(205,133,63));
        break;
    case 512:
        //巧克力
        return QBrush(qRgb(210,105,30));
        break;
    case 1024:
        //赭色
        return QBrush(qRgb(160,82,45));
        break;
    case 2048:
        //鞍棕色
        return QBrush(qRgb(139,69,19));
        break;
    default:
        break;
    }
    return QBrush();
}

/* 数字向上合并 */
void gameView::moveFront()
{
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[j][i]!=0&&array[j][i]==array[j-k][i]){
                    array[j-k][i]=0;
                    array[j][i]*=2;
                    updatePoint(j*4+i,array[j][i]);
                    clearPoint((j-k)*4+i);
                    updateScore(array[j][i]);
                    k++;
                }else if(array[j-k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(array[j][i]==0){
                for(int k=j+1;k<4;k++){
                    if(array[k][i]!=0){
                        array[j][i]=array[k][i];
                        array[k][i]=0;
                        updatePoint(j*4+i,array[j][i]);
                        clearPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}

/* 数字向左合并 */
void gameView::moveLeft()
{
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(array[i][j]!=0&&array[i][j]==array[i][j-k]){
                    array[i][j-k]=0;
                    array[i][j]*=2;
                    updatePoint(i*4+j,array[i][j]);
                    clearPoint(i*4+j-k);
                    updateScore(array[i][j]);
                    k++;
                }else if(array[i][j-k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(array[i][j]==0){
                for(int k=j+1;k<4;k++){
                    if(array[i][k]!=0){
                        array[i][j]=array[i][k];
                        array[i][k]=0;
                        updatePoint(i*4+j,array[i][j]);
                        clearPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}

/* 数字向右合并 */
void gameView::moveRight()
{
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[i][j]!=0&&array[i][j]==array[i][j+k]){
                    array[i][j+k]=0;
                    array[i][j]*=2;
                    updatePoint(i*4+j,array[i][j]);
                    clearPoint(i*4+j+k);
                    updateScore(array[i][j]);
                    k++;
                }else if(array[i][j+k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(array[i][j]==0){
                for(int k=j-1;k>=0;k--){
                    if(array[i][k]!=0){
                        array[i][j]=array[i][k];
                        array[i][k]=0;
                        updatePoint(i*4+j,array[i][j]);
                        clearPoint(i*4+k);
                        break;
                    }
                }
            }
        }
    }
}

/* 数字向下合并 */
void gameView::moveBehind()
{
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(array[j][i]!=0&&array[j][i]==array[j+k][i]){
                    array[j+k][i]=0;
                    array[j][i]*=2;
                    updatePoint(j*4+i,array[j][i]);
                    clearPoint((j+k)*4+i);
                    updateScore(array[j][i]);
                    k++;
                }else if(array[j+k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(array[j][i]==0){
                for(int k=j-1;k>=0;k--){
                    if(array[k][i]!=0){
                        array[j][i]=array[k][i];
                        array[k][i]=0;
                        updatePoint(j*4+i,array[j][i]);
                        clearPoint(k*4+i);
                        break;
                    }
                }
            }
        }
    }
}

/* 判断游戏是否结束 */
bool gameView::isOver()
{
    /* 即判断屏幕上是否还存在可合成的数字，存在则返回 false，未结束游戏，反之则返回 true，结束游戏 */
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i+1<4&&array[i][j]==array[i+1][j])
                return false;
            if(j+1<4&&array[i][j]==array[i][j+1])
                return false;
        }
    }
    return true;
}
#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , record(new recordTable)
    , screen(new gameScreen)
    , game(new gameView)
{
    /* 初始化主窗口的菜单和游戏部分 */
    initalMenu();
    initalGame();
}

MainWindow::~MainWindow()
{
    /* 释放动态分配的内存 */
    delete record;
    delete screen;
    delete game;
}

/* 初始化菜单模块 */
void MainWindow::initalMenu()
{
    /* 获取当前窗口的 QMenuBar 指针 */
    menu=menuBar();
    /* 添加两个菜单 */
    startMenu=menu->addMenu(tr("start"));
    helpMenu=menu->addMenu(tr("help"));
    /* 创建菜单对应的 QAction */
    QAction* startAction=new QAction(tr("start game"));
    QAction* recordAction=new QAction(tr("open record"));
    QAction* clearAction=new QAction(tr("clear record"));
    QAction* exitAction=new QAction(tr("exit"));
    QAction* aboutAction=new QAction(tr("about"));
    /* 添加QAction 到 startMenu 菜单里 */
    startMenu->addAction(startAction);
    startMenu->addAction(recordAction);
    startMenu->addAction(clearAction);
    startMenu->addAction(exitAction);
    /* 添加QAction 到 helpMenu 菜单里 */
    helpMenu->addAction(aboutAction);
    /* 为 startAction 添加触发的动作：打开游戏屏幕(gameScreen)并初始化游戏(gameView) */
    connect(startAction,&QAction::triggered,this,[=](){
        screen->show();
        game->startGame();
    });
    /* 为 recordAction 添加触发的动作：显示记录窗口 */
    connect(recordAction,&QAction::triggered,record,&QWidget::show);
    /* 为 clearAction 添加触发的动作：清除记录 */
    connect(clearAction,&QAction::triggered,record,&recordTable::clear);
    /* 为 exitAction 添加触发的动作：关闭游戏屏幕(gameScreen) */
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    /* 为 aboutAction 添加触发的动作：显示一个 about 弹窗 */
    connect(aboutAction,&QAction::triggered,this,[=](){
        QMessageBox::about(this,tr("About"),tr("This is a little game."));
    });
}

/* 初始化游戏模块 */
void MainWindow::initalGame()
{
    /* 调整记录窗口标题、窗口大小、记录的内容 */
    record->setWindowTitle(tr("Game Record"));
    record->resize(400,400);
    record->setTableTitle(QStringList()<<tr("Cost Time")<<tr("Score"));
    /* 为游戏屏幕(gameScreen)设置游戏窗口(gameView) */
    screen->setGame(game);
    /* 将屏幕的移动信号(moveTo)连接到游戏的移动操作处理的槽函数 */
    connect(screen,&gameScreen::moveTo,game,&gameView::moveTo);
    /* 获取游戏结算的时间，并记录起来 */
    connect(game,&gameView::settleTime,this,[=](double costTime){
        info.first=costTime;
    });
    /* 获取游戏结算的分数，并记录起来，将记录存储到记录窗口内 */
    connect(game,&gameView::settleScore,this,[=](int score){
        info.second=score;
        record->addRecord(QStringList()<<QString::number(info.first)<<QString::number(info.second));
    });
    /* 游戏发出的关闭游戏信号(此时游戏已做好善后处理)将触发游戏屏幕的关闭 */
    connect(game,&gameView::closeGame,screen,&gameScreen::close);
}
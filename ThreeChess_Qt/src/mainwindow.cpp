#include "mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , record(new recordTable)
    , screen(new gameScreen)
    , game(new gameView)
{
    initalMenu();
    initalGame();
}

MainWindow::~MainWindow()
{
    delete record;
    delete screen;
    delete game;
}

void MainWindow::initalMenu()
{
    menu=menuBar();
    startMenu=menu->addMenu(tr("start"));
    helpMenu=menu->addMenu(tr("help"));
    QAction* startAction=new QAction(tr("start game"));
    QAction* recordAction=new QAction(tr("open record"));
    QAction* clearAction=new QAction(tr("clear record"));
    QAction* exitAction=new QAction(tr("exit"));
    QAction* aboutAction=new QAction(tr("about"));
    startMenu->addAction(startAction);
    startMenu->addAction(recordAction);
    startMenu->addAction(clearAction);
    startMenu->addAction(exitAction);
    helpMenu->addAction(aboutAction);
    connect(startAction,&QAction::triggered,this,[=](){
        screen->show();
        game->startGame();
    });
    connect(recordAction,&QAction::triggered,this,[=](){
        record->show();
    });
    connect(clearAction,&QAction::triggered,this,[=](){
        record->clear();
    });
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){
        QMessageBox::about(this,tr("about"),tr("This a little game."));
    });
}

void MainWindow::initalGame()
{
    record->setTableTitle(QStringList()<<tr("Winner")<<tr("Cost Time"));
    screen->setGame(game);
    connect(game,&gameView::closeGame,screen,&QWidget::close);
    connect(game,&gameView::settlePlayer,this,[=](const QString& player){
        info.first=player;
    });
    connect(game,&gameView::settleTime,this,[=](double time){
        info.second=time;
        record->addRecord(QStringList()<<info.first<<QString::number(info.second));
    });
}
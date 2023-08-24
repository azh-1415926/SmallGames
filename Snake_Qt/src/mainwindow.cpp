
#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>

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
    connect(recordAction,&QAction::triggered,record,&QWidget::show);
    connect(clearAction,&QAction::triggered,record,&recordTable::clear);
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"About","This is a little game.");
    });
}

void MainWindow::initalGame()
{
    record->setTableTitle(QStringList()<<tr("Cost Time")<<tr("Length"));
    screen->setGame(game);
    screen->resize(600,600);
    connect(screen,&gameScreen::clicked,game,&gameView::clickPoint);
    connect(screen,&gameScreen::moveTo,game,&gameView::moveTo);
    connect(game,&gameView::closeGame,screen,&gameScreen::close);
    connect(game,&gameView::settleTime,this,[=](double time){
        info.first=time;
    });
    connect(game,&gameView::settleLength,this,[=](int length){
        info.second=length;
        record->addRecord(QStringList()<<QString::number(info.first)<<QString::number(info.second));
    });
}
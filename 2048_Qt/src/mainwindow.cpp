#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , menu(menuBar())
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
    connect(screen,&gameScreen::moveTo,game,&gameView::moveTo);
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
        QMessageBox::about(this,tr("About"),tr("This is a little game."));
    });
}

void MainWindow::initalGame()
{
    record->setWindowTitle(tr("Game Record"));
    record->resize(400,400);
    record->setTableTitle(QStringList()<<tr("Cost Time")<<tr("Score"));
    screen->setGame(game);
    connect(game,&gameView::settleTime,[=](double costTime){
        info.first=costTime;
    });
    connect(game,&gameView::settleScore,[=](int score){
        info.second=score;
        record->addRecord(QStringList()<<QString::number(info.first)<<QString::number(info.second));
    });
    connect(game,&gameView::closeGame,[=](){
        screen->close();
    });
}
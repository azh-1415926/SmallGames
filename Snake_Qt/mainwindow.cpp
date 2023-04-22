#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , menu(menuBar())
    , record(new QTableWidget(this))
    , screen(new GameScreen)
    , snake(new SnakeAction)
{
    record->setGeometry(25,50,450,400);
    record->setColumnCount(3);
    record->setRowCount(5);
    record->setHorizontalHeaderLabels(QStringList()<<tr("Player")<<tr("Cost Time")<<tr("Score"));
    connect(screen,&GameScreen::clickScreen,snake,&SnakeAction::moveAction);
    connect(snake,&SnakeAction::moveHead,screen,&GameScreen::updateHead);
    connect(snake,&SnakeAction::moveTail,screen,&GameScreen::updateTail);
    connect(screen,&GameScreen::closeGame,this,[=](){
        snake->clearSnake();
        screen->close();
        killTimer(timerId);
    });
    connect(snake,&SnakeAction::removeBody,screen,&GameScreen::removePoint);
    initalMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    snake->moveTo(-1);
}

void MainWindow::initalMenu(){
    startMenu=menu->addMenu(tr("start"));
    helpMenu=menu->addMenu(tr("help"));
    QAction* startAction=new QAction(tr("start game"));
    QAction* clearAction=new QAction(tr("clear record"));
    QAction* exitAction=new QAction(tr("exit"));
    QAction* aboutAction=new QAction(tr("about"));
    startMenu->addAction(startAction);
    startMenu->addAction(clearAction);
    startMenu->addAction(exitAction);
    helpMenu->addAction(aboutAction);
    connect(startAction,&QAction::triggered,this,[=](){
        screen->show();
        timerId=startTimer(1000);
    });
    connect(clearAction,&QAction::triggered,this,[=](){
        record->clear();
        record->setHorizontalHeaderLabels(QStringList()<<tr("Player")<<tr("Cost Time")<<tr("Score"));
    });
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){

    });
}

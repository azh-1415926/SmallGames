
#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , menu(menuBar())
    , recordTable(new QTableWidget(this))
    , screen(new GameScreen)
    , snake(new SnakeAction)
    , control(new GameControl)
{
    initalMenu();
    initalRecord();
    initalGame();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initalMenu()
{
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
        control->startGame();
        screen->updatePoint(40);
        snake->initalSnake();
        screen->show();
        screen->addFood();
    });
    connect(clearAction,&QAction::triggered,this,[=](){
        recordTable->clear();
        recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Player")<<tr("Cost Time")<<tr("Score"));
    });
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){

    });
}

void MainWindow::initalRecord()
{
    recordTable->setGeometry(50,100,400,300);
    recordTable->setColumnCount(3);
    recordTable->setRowCount(5);
    recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Player")<<tr("Cost Time")<<tr("Score"));
}

void MainWindow::initalGame()
{
    connect(screen,&GameScreen::clickScreen,control,&GameControl::moveSnake);
    connect(screen,&GameScreen::findFood,snake,&SnakeAction::eatFood);
    connect(screen,&GameScreen::closeGame,this,[=](){
        snake->clearSnake();
        screen->clearScreen();
        screen->close();
    });
    connect(control,&GameControl::moving,snake,&SnakeAction::moveTo);
    connect(control,&GameControl::moveHead,screen,&GameScreen::updatePoint);
    connect(control,&GameControl::moveTail,screen,&GameScreen::clearPoint);
    connect(snake,&SnakeAction::moveHead,control,&GameControl::updateHead);
    connect(snake,&SnakeAction::moveTail,control,&GameControl::updateTail);
    connect(snake,&SnakeAction::eatFood,screen,&GameScreen::addFood);
}



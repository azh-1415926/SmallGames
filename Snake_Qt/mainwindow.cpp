
#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>

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

void MainWindow::setTime(double time)
{
    if(i>=5){
        return;
    }
    recordTable->setItem(i,0,new QTableWidgetItem(QString::number(time)));
}

void MainWindow::setLength(int length)
{
    if(i>=5){
        return;
    }
    recordTable->setItem(i,1,new QTableWidgetItem(QString::number(length)));
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
    connect(startAction,&QAction::triggered,this,&MainWindow::startGame);
    connect(clearAction,&QAction::triggered,this,[=](){
        recordTable->clear();
        recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Cost Time")<<tr("Length"));
        i=0;
    });
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){
        QMessageBox::about(this,"About","This is a little game.");
    });
}

void MainWindow::initalRecord()
{
    i=0;
    recordTable->setGeometry(50,100,400,300);
    recordTable->setColumnCount(2);
    recordTable->setRowCount(5);
    recordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Cost Time")<<tr("Length"));
}

void MainWindow::initalGame()
{
    connect(this,&MainWindow::startGame,[=](){
        control->initalControl();
        screen->initalScreen();
        snake->initalSnake();

    });
    connect(screen,&GameScreen::clickScreen,control,&GameControl::moveSnake);
    connect(screen,&GameScreen::pressKeyboard,control,&GameControl::moveTo);
    connect(screen,&GameScreen::findFood,snake,&SnakeAction::eatFood);
    connect(screen,&GameScreen::closeGame,control,&GameControl::closeGame);
    connect(control,&GameControl::exitGame,this,[=](){
        snake->clearSnake();
        snake->getLength();
        screen->clearScreen();
        screen->close();
        i++;
    });
    connect(control,&GameControl::restartGame,this,[=](){
        emit control->exitGame();
        emit startGame();
    });
    connect(control,&GameControl::moving,snake,&SnakeAction::moveTo);
    connect(control,&GameControl::moveHead,screen,&GameScreen::updatePoint);
    connect(control,&GameControl::moveTail,screen,&GameScreen::clearPoint);
    connect(control,&GameControl::costTime,this,&MainWindow::setTime);

    connect(snake,&SnakeAction::moveHead,control,&GameControl::updateHead);
    connect(snake,&SnakeAction::moveTail,control,&GameControl::updateTail);
    connect(snake,&SnakeAction::sendLength,this,&MainWindow::setLength);
}



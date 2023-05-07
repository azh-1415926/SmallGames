
#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , menu(menuBar())
    , recordTable(new QTableWidget(this))
    , screen(new GameScreen)
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

void MainWindow::setScore(int score)
{
    if(i>=5){
        return;
    }
    recordTable->setItem(i,1,new QTableWidgetItem(QString::number(score)));
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
        recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Cost Time")<<tr("Score"));
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
    recordTable->setHorizontalHeaderLabels(QStringList()<<tr("Cost Time")<<tr("Score"));
}

void MainWindow::initalGame()
{
    connect(this,&MainWindow::startGame,[=](){
        control->initalControl();
        screen->show();
    });
    connect(screen,&GameScreen::goTo,control,&GameControl::moving);
    connect(control,&GameControl::addPoint,screen,&GameScreen::updatePoint);
    connect(control,&GameControl::delPoint,screen,&GameScreen::clearPoint);
    connect(control,&GameControl::exitGame,this,[=](){
        screen->clearScreen();
        screen->close();
        i++;
    });
    connect(control,&GameControl::restartGame,this,[=](){
        screen->clearScreen();
        screen->close();
        i++;
        emit startGame();
    });

    connect(control,&GameControl::costTime,this,&MainWindow::setTime);
    connect(control,&GameControl::sendScore,this,&MainWindow::setScore);
}


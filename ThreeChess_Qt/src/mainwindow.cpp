#include "mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , chess(new ChessBoard)
    , control(new GameControl)
    , recordTab(new QTableWidget(this))
    , recordCount(5)
    , currCount(0)
{
    menu=menuBar();
    startMenu=menu->addMenu(tr("start"));
    helpMenu=menu->addMenu(tr("help"));
    initalMenu();
    recordTab->setGeometry(50,100,400,300);
    recordTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordTab->setColumnCount(3);
    recordTab->setHorizontalHeaderLabels(QStringList()<<tr("Number")<<tr("Winner")<<tr("Cost Time"));
    recordTab->setRowCount(recordCount);
}

MainWindow::~MainWindow()
{
    delete chess;
    delete control;
}

void MainWindow::addRecord(QString const&gamer, int time)
{
    if(currCount==recordCount){
        return;
    }
    recordTab->setItem(currCount,0,new QTableWidgetItem(QString::number(currCount+1)));
    recordTab->setItem(currCount,1,new QTableWidgetItem(gamer));
    recordTab->setItem(currCount,2,new QTableWidgetItem(QString::number(time/1000.0)));
    currCount++;
}
void MainWindow::initalMenu()
{
    QAction* startGameAction=new QAction(tr("start game"));
    QAction* clearRecordAction=new QAction(tr("clear record"));
    QAction* exitAction=new QAction(tr("exit"));
    QAction* aboutAction=new QAction(tr("about"));
    startMenu->addAction(startGameAction);
    startMenu->addAction(clearRecordAction);
    startMenu->addAction(exitAction);
    helpMenu->addAction(aboutAction);
    //menubar
    connect(startGameAction,&QAction::triggered,control,&GameControl::initalGame);
    connect(clearRecordAction,&QAction::triggered,this,[=](){
        recordTab->clear();
        recordTab->setHorizontalHeaderLabels(QStringList()<<tr("Number")<<tr("Winner")<<tr("Cost Time"));
        currCount=0;
    });
    connect(exitAction,&QAction::triggered,this,&QMainWindow::close);
    connect(aboutAction,&QAction::triggered,this,[=](){
        QMessageBox::about(this,tr("about"),tr("This a little game."));
    });
    //gamecontrol
    connect(control,&GameControl::startGame,chess,&ChessBoard::showBoard);
    connect(control,&GameControl::restartGame,this,[=](){
        chess->close();
        chess->clearBoard();
        control->initalGame();
    });
    connect(control,&GameControl::closeGame,this,[=](){
        chess->close();
        chess->clearBoard();
    });
    connect(control,&GameControl::record,this,&MainWindow::addRecord);
    //boardaction
    connect(chess,&ChessBoard::clickBoard,control,&GameControl::getOption);
    connect(chess,&ChessBoard::setSuccess,control,&GameControl::switchNextGamer);
    connect(control,&GameControl::sendOption,chess,&ChessBoard::addChequer);
    connect(chess,&ChessBoard::settleGame,control,&GameControl::settleGame);
}


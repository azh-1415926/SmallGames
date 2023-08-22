#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include "recordtable.h"
#include "gamescreen.h"
#include "gameview.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    ;

public slots:
    ;

private:
    QMenuBar* menu;
    QMenu* startMenu;
    QMenu* helpMenu;
    recordTable* record;
    gameScreen* screen;
    gameView* game;
    QPair<double,int> info;
    void initalMenu();
    void initalGame();
};
#pragma once
#include <QMainWindow>
#include "recordtable.h"
#include "gamescreen.h"
#include "gameview.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    ;

signals:
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
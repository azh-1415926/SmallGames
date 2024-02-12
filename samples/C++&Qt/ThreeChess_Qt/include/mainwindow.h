#pragma once
#include <QMainWindow>
#include "gameview.h"
#include "recordtable.h"
#include "gamescreen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenuBar* menu;
    QMenu* startMenu;
    QMenu* helpMenu;
    recordTable* record;
    gameScreen* screen;
    gameView* game;
    QPair<QString,double> info;
    void initalMenu();
    void initalGame();
};
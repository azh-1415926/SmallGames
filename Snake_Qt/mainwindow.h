
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "snakeaction.h"
#include "gamescreen.h"
#include "gamecontrol.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void clearRecord();
private:
    QMenuBar* menu;
    QMenu* startMenu;
    QMenu* helpMenu;
    QTableWidget* recordTable;
    GameScreen* screen;
    SnakeAction* snake;
    GameControl* control;
    void initalMenu();
    void initalRecord();
    void initalGame();
};

#endif // MAINWINDOW_H

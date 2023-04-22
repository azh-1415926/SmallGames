#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTableWidget>
#include <QTimer>
#include "gamescreen.h"
#include "snakeaction.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void clearRecord();
protected:
    void timerEvent(QTimerEvent* event) override;
private:
    QMenuBar* menu;
    QMenu* startMenu;
    QMenu* helpMenu;
    QTableWidget* record;
    GameScreen* screen;
    SnakeAction* snake;
    int timerId;
    void initalMenu();
};
#endif // MAINWINDOW_H

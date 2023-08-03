#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QTableWidget>
#include "chessboard.h"
#include "GameControl.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addRecord(QString const& gamer,int time);
private:
    ChessBoard* chess;
    GameControl* control;
    QMenuBar* menu;
    QMenu* startMenu;
    QMenu* helpMenu;
    QTableWidget* recordTab;
    int recordCount;
    int currCount;
    void initalMenu();
};
#endif // MAINWINDOW_H

#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class gameView:public QWidget
{
    Q_OBJECT

public:
    gameView(QWidget* parent=nullptr);
    ~gameView();

protected:
    ;

public slots:
    void startGame();
    void clearView();
    void clickPoint(const QPoint& p);
    void doComputer();

signals:
    void sendOption(int pos);
    void settlePlayer(const QString&);
    void settleTime(double);
    void closeGame();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup *group;
    int flagOfGame;
    int startTime;
    QList<QGraphicsEllipseItem*> chequers;
    QColor currColor;
    QPair<QColor,QColor> colorOfChequer;
    void initalView();
    void initalGame();
    void addChequer(int pos);
    void setChequer(int pos);
    void switchNextPlayer();
    int getComputerOption();
    int getPlayerOptionByPoint(const QPoint& p);
    bool isWin(int pos);
    void settleGame(const QString& tip);
};
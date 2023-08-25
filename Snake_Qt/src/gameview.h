#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QQueue>

class gameView : public QWidget
{
    Q_OBJECT

public:
    gameView(QWidget* parent=nullptr);
    ~gameView();

protected:
    void timerEvent(QTimerEvent* e) override;

public slots:
    void startGame();
    void clearView();
    void moveTo(int direction);

signals:
    void settleTime(double);
    void settleLength(int);
    void closeGame();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup* group;
    int timerId;
    int lastDirection;
    int head;
    int tail;
    int flagOfTime;
    int flagOfGame;
    double startTime;
    QQueue<QPoint> snake;
    QGraphicsRectItem* food;
    QList<QGraphicsRectItem*> blocks;
    void initalView();
    void initalGame();
    void settleGame();
    void moving(int direction);
    void updateHead(QPoint const& head);
    void updateTail(QPoint const& tail);
    void updateBlock(int pos);
    void clearBlock(int pos);
    void addFood();
};
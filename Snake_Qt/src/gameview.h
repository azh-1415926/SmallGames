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
    void closeEvent(QCloseEvent* e) override;

public slots:
    void startGame();
    void clickPoint(const QPoint &p);
    void moveTo(int direction);
    void moving(int direction);
    void updateHead(QPoint const& head);
    void updateTail(QPoint const& tail);
    void updatePoint(int pos);
    void clearPoint(int pos);
    void addFood();

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
    QList<QGraphicsRectItem*> snakeShape;
    void initalView();
    void initalGame();
    void clearView();
    void settleGame();
};
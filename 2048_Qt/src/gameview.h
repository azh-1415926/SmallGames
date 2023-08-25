#pragma once
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class gameView : public QWidget
{
    Q_OBJECT
public:
    gameView(QWidget* parent=nullptr);
    ~gameView();

protected:
    void timerEvent(QTimerEvent *event) override;

public slots:
    void startGame();
    void clearView();
    void moveTo(int direction);

signals:
    void settleScore(int);
    void settleTime(double);
    void closeGame();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup* group;
    QList<QGraphicsRectItem*> blocks;
    QList<QGraphicsTextItem*> numbers;
    double startTime;
    int timerId;
    int array[4][4];
    int maxNumber;
    int zeroCount;
    int score;
    int flagOfGame;
    int flagOfTime;
    void initalView();
    void initalGame();
    void settleGame();
    void addNumber();
    void updatePoint(int pos,int num);
    void clearPoint(int pos);
    void updateScore(int score);
    QBrush getBrushByNum(int i);
    void moveFront();
    void moveLeft();
    void moveRight();
    void moveBehind();
    bool isOver();
};
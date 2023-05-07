
#ifndef GAMECONTROL_H
#define GAMECONTROL_H


#include <QObject>
#include <QPoint>
#include <QTime>

class GameControl : public QObject
{
    Q_OBJECT
public:
    GameControl(QObject* parent=nullptr);
signals:
    void costTime(double time);
    void sendScore(int score);
    void restartGame();
    void addPoint(int pos,int num);
    void delPoint(int pos);
    void exitGame();
public slots:
    void initalControl();
    void moving(int direction);
    void addNumber();
    void updateScore(int score);
    void setFlag();
    void resetFlag();
    void closeGame();
protected:
    void timerEvent(QTimerEvent *event) override;
private:
    int array[4][4]={0};
    int timerId;
    int flag;
    int maxNumber;
    int totalScore;
    int zeroCount;
    double startTime;
    void moveFront();
    void moveLeft();
    void moveRight();
    void moveBehind();
    bool isOver();
};

#endif // GAMECONTROL_H

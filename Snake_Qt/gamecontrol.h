
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
protected:
    virtual void timerEvent(QTimerEvent* event) override;
signals:
    void moving(int direction);
    void moveHead(int pos);
    void moveTail(int pos);
    void costTime(double time);
    void restartGame();
    void exitGame();
public slots:
    void initalControl();
    void moveTo(int direction);
    void moveSnake(QPoint const& point);
    void updateHead(QPoint const& head);
    void updateTail(QPoint const& tail);
    void clearGame();
    void closeGame();
private:
    int timerId;
    int lastDirection;
    int head;
    int tail;
    int flag;
    double startTime;
};

#endif // GAMECONTROL_H

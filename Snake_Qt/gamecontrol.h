
#ifndef GAMECONTROL_H
#define GAMECONTROL_H


#include <QObject>
#include <QPoint>


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
public slots:
    void startGame();
    void moveSnake(QPoint const& point);
    void updateHead(QPoint const& head);
    void updateTail(QPoint const& tail);
    void exitGame();
private:
    int timerId;
    int lastDirection;
    int head;
    int tail;
};

#endif // GAMECONTROL_H

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include <QColor>

class GameControl:public QObject
{
    Q_OBJECT
public:
    GameControl(QObject* parent=nullptr);
signals:
    void startGame();
    void closeGame();
    void restartGame();
    void sendOption(int pos,QColor const& color);
    void record(QString const& gamer,int time);
public slots:
    void initalGame();
    void settleGame(QString const& content);
    void getOption(int pos);
    void switchNextGamer();
private:
    QColor playerColor;
    QColor computerColor;
    QColor currColor;
    int gameFlag;
    int startTime;
    int endTime;
    int computerOption();
protected:
};

#endif // GAMECONTROL_H

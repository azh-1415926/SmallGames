#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class ChessBoard:public QWidget
{
    Q_OBJECT
public:
    ChessBoard(QWidget* parent=nullptr);
signals:
    void clickBoard(int pos);
    void setSuccess();
    void settleGame(QString const& content);
public slots:
    void showBoard();
    void clearBoard();
    void addChequer(int pos,QColor const& color);
private:
    QGraphicsScene* boardScene;
    QGraphicsView* widgetView;
    QList<QGraphicsEllipseItem*> chequers;
    QColor currColor;
    //QColor lastColor;
    void initalBoard();
    void setChequer(int pos);
    int playerAction(int x,int y);
    bool isWin(int pos);
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CHESSBOARD_H

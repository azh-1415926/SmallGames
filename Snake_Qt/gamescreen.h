
#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QQueue>


class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget* parent=nullptr);
signals:
    void clickScreen(QPoint const& point);
    void closeGame();
public slots:
    void updateHead(QPoint const& head);
    void updateTail(QPoint const& tail);
    void removePoint(QPoint const& point);
protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup* group;
    QGraphicsRectItem* head;
    QGraphicsRectItem* tail;
    QList<QGraphicsRectItem*> snakeShape;
    void initalGame();
};

#endif // GAMESCREEN_H

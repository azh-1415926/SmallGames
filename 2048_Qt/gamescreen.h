
#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget* parent=nullptr);
signals:
    void goTo(int direction);
public slots:
    void updatePoint(int pos,int num);
    void clearPoint(int pos);
    void clearScreen();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup* group;
    QList<QGraphicsRectItem*> background;
    QList<QLabel*> number;
    QPoint clickPoint;
    void initalScreen();
};

#endif // GAMESCREEN_H

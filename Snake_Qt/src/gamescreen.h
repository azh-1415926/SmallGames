
#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class GameScreen : public QWidget
{
    Q_OBJECT
public:
    GameScreen(QWidget* parent=nullptr);
    ~GameScreen();
signals:
    void clickScreen(QPoint const& point);
    void pressKeyboard(int direction);
    void findFood(int pos);
    void clearGame();
    void exitGame();
public slots:
    void initalScreen();
    void updatePoint(int pos);
    void clearPoint(int pos);
    void addFood();
    void clearScreen();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsItemGroup* group;
    QGraphicsRectItem* food;
    QList<QGraphicsRectItem*> snakeShape;
    void inital();
};

#endif // GAMESCREEN_H

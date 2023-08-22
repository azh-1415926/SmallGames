#pragma once
#include <QWidget>
#include <QHBoxLayout>

class gameScreen : public QWidget
{
    Q_OBJECT

public:
    gameScreen(QWidget* parent=nullptr);
    ~gameScreen();
    enum moveDirection {
        directionOfFront,
        directionOfRight,
        directionOfBehind,
        directionOfLeft
    };

signals:
    void moveTo(enum moveDirection);
    void clicked(const QPoint&);

public slots:
    void setGame(QWidget* game);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QPoint clickPoint;
    QHBoxLayout* layout;
    void initalScreen();
};
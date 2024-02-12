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

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* e) override;

public slots:
    void setGame(QWidget* game);

signals:
    void moveTo(enum moveDirection);
    void clicked(const QPoint&);
    void closed();

private:
    QPoint clickPoint;
    QHBoxLayout* layout;
    QWidget* game;
    void initalScreen();
};
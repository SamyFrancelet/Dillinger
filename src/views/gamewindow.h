#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "gameLogic/controller.h"
#include "observer.h"

class GameWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void setController(Controller* c);

    // Observer interface
public:
    void refresh();
    void stop();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Controller* _c;
};
#endif // GAMEWINDOW_H

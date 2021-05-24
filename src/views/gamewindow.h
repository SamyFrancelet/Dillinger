#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <gameLogic/physicsengine.h>
#include "observer.h"

class GameWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void setController(PhysicsEngine* c);

    // Observer interface
public:
    void refresh();
    void stop();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    PhysicsEngine* _c;
};
#endif // GAMEWINDOW_H

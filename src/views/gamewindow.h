#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "gameLogic/gamelogic.h"
#include "observer.h"

class GameWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void setController(GameLogic* c);

    // Observer interface
public:
    void refresh();
    void stop();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

private:
    GameLogic* _c;
};
#endif // GAMEWINDOW_H

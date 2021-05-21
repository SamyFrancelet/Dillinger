#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "observer.h"

class GameWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // Observer interface
public:
    void refresh();
    void stop();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};
#endif // GAMEWINDOW_H

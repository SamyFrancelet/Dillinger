#include "gamewindow.h"
#include "scenes/scene.h"
#include <QPainter>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1280, 900);
}

GameWindow::~GameWindow()
{
}

void GameWindow::refresh()
{
    update();
}

void GameWindow::stop()
{
    this->close();
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    _s->draw(&p);
}


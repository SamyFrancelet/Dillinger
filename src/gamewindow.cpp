#include "gamewindow.h"
#include "scene.h"
#include <QPainter>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(800, 800);
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


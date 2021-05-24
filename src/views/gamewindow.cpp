#include "gamewindow.h"
#include "scenes/scene.h"
#include <QPainter>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
{
    this->setFixedSize(1280, 900);
}

GameWindow::~GameWindow()
{
}

void GameWindow::setController(PhysicsEngine *c)
{
    _c = c;
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
    qDebug() << "Painting";
    QPainter p(this);
    _s->draw(&p);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Press";
    _c->simulate_step();
}


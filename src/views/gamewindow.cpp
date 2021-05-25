#include "gamewindow.h"
#include "scenes/scene.h"
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent)
{
    this->setFixedSize(1280, 900);
}

GameWindow::~GameWindow()
{
}

void GameWindow::setController(GameLogic *c)
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
    QPainter p(this);
    _s->draw(&p);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() ){
        _c->keyPressed(event->key());
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() ){
        _c->keyReleased(event->key());
    }
}


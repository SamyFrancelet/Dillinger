#include "gamewindow.h"
#include "gameConstants.h"
#include "scenes/scene.h"
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent)
{
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

GameWindow::~GameWindow()
{
}

void GameWindow::setController(Controller *c)
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

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->scenePosition();
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << event->scenePosition();
    //event->scenePosition();
}


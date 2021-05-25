#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameObjects/dynamicentity.h"
#include "gameObjects/wall.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameLogic* p = new GameLogic();

    GameScene* s = new GameScene();
    p->setScene(s);

    GameWindow* g = new GameWindow();
    g->setController(p);
    g->setScene(s);

    g->show();

    DynamicEntity* d = new DynamicEntity(20,20);
    s->addEntity(d);
    d->setPos(100,100);
    d->setSpeed(1,1);

    Wall* w = new Wall(10, 100);
    w->setPos(50,50);
    s->addEntity(w);

    s->changed();

    return a.exec();
}

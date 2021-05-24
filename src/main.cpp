#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameObjects/dynamicentity.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PhysicsEngine* p = new PhysicsEngine();

    GameScene* s = new GameScene();
    p->setScene(s);

    GameWindow* w = new GameWindow();
    w->setController(p);
    w->setScene(s);

    w->show();

    DynamicEntity* d = new DynamicEntity();
    s->addEntity(d);
    d->setPos(100,100);
    d->setSpeed(1,1);

    s->changed();

    return a.exec();
}

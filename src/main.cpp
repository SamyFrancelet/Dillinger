#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameObjects/entity.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Entity test;
    test.setPos(200, 200);

    GameScene s;
    s.addEntity(&test);

    GameWindow w;
    w.setScene(&s);

    s.changed();

    w.show();
    return a.exec();
}

#include "gamewindow.h"
#include "gamescene.h"
#include "entity.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Entity test;
    test.setPos(100,100);

    GameScene s;
    s.addEntity(&test);

    GameWindow w;
    w.setScene(&s);

    s.changed();

    w.show();
    return a.exec();
}

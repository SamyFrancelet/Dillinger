#include "dillinger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dillinger game;
    game.loadLevel(1);

    return a.exec();
}

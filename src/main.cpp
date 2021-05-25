#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameObjects/player.h"
#include "gameObjects/wall.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameLogic* p = new GameLogic(0.05);

    GameScene* s = new GameScene();
    p->setScene(s);

    Player* player = new Player();
    player->setPos(500,500);
    s->addPlayer(player);

    Wall* topBorder = new Wall(1280, 0.1);
    Wall* leftBorder = new Wall(0.1, 900);
    Wall* bottomBorder = new Wall(1280, 0.1);
    bottomBorder->moveBy(0, 900);
    Wall* rightBorder = new Wall(0.1, 900);
    rightBorder->moveBy(1280, 0);

    s->addEntity(topBorder);
    s->addEntity(leftBorder);
    s->addEntity(bottomBorder);
    s->addEntity(rightBorder);

    Wall* wall = new Wall(200, 40);
    wall->setPos(50,50);
    s->addEntity(wall);

    GameWindow* g = new GameWindow();
    g->setController(p);
    g->setScene(s);

    g->show();

    s->changed();

    return a.exec();
}

#include "dillinger.h"

Dillinger::Dillinger()
{

}

void Dillinger::loadLevel(int level)
{
    _g = new GameWindow();
    _c = new GameLogic(0.05);
    _s = new GameScene();

    _g->setScene(_s);
    _g->setController(_c);
    _c->setScene(_s);

    Player* p = new Player();
    p->setPos(500,500);
    _s->addPlayer(p);

    _g->show();
}

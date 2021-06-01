
#include "dillinger.h"

Dillinger::Dillinger()
{

}

void Dillinger::loadLevel(int level)
{
    _g = new GameWindow();
    _c = new GameLogic(0.05);
    _s = new GameScene();

    Player* p = new Player();
    p->setPos(60,60);
    _s->addPlayer(p);

    Enemy* schlaggados = new Enemy();
    schlaggados->setPos(600,500);
    schlaggados->setAngle(72);
    _s->addEntity(schlaggados);

    Wall* w1 = new Wall(200, 20);
    w1->setPos(0,200);
    _s->addEntity(w1);

    Wall* w2 = new Wall(20, 600);
    w2->setPos(280, 0);
    _s->addEntity(w2);

    Wall* w3 = new Wall(20, 200);
    w3->setPos(280, 700);
    _s->addEntity(w3);

    Wall* w4 = new Wall(20, 420);
    w4->setPos(500, 0);
    _s->addEntity(w4);

    Wall* w5 = new Wall(340, 20);
    w5->setPos(520, 400);
    _s->addEntity(w5);

    Wall* w6 = new Wall(400, 20);
    w6->setPos(940, 400);
    _s->addEntity(w6);

    Wall* w7 = new Wall(640, 20);
    w7->setPos(520, 760);
    _s->addEntity(w7);

    Wall* w8 = new Wall(20, 400);
    w8->setPos(500, 500);
    _s->addEntity(w8);

    _g->setScene(_s);
    _g->setController(_c);
    _c->setScene(_s);

    _g->show();
}

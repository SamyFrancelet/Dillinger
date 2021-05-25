#ifndef DILLINGER_H
#define DILLINGER_H

#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameLogic/gamelogic.h"
#include "gameObjects/player.h"
#include "gameObjects/wall.h"

class Dillinger
{
public:
    Dillinger();

    void loadLevel(int level);

private:
    GameWindow* _g;
    GameScene* _s;
    GameLogic* _c;
};

#endif // DILLINGER_H

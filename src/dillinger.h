#ifndef DILLINGER_H
#define DILLINGER_H

#include "views/gamewindow.h"
#include "scenes/gamescene.h"
#include "gameLogic/gamelogic.h"
#include "gameObjects/player.h"
#include "gameObjects/enemy.h"
#include "gameObjects/wall.h"
#include "gameObjects/glass.h"

/**
 * @brief The Dillinger class
 * Used to launch a game of the Dillinger game
 * Singleton pattern, so you can get the instance from everywhere
 */
class Dillinger
{
public:
    static Dillinger* getInstance();

    void loadLevel(int level);

private:
    Dillinger();

    static Dillinger* instance;

    GameWindow* _g;
    GameScene* _s;
    GameLogic* _c;
};

#endif // DILLINGER_H

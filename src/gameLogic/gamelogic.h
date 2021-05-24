#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "scenes/gamescene.h"

class GameLogic
{
public:
    GameLogic();

    void setScene(GameScene* scene);

    void move_step();

private:
    GameScene* _scene;
    qreal delta_t;
};

#endif // GAMELOGIC_H

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "scenes/gamescene.h"

class PhysicsEngine
{
public:
    PhysicsEngine();

    void setScene(GameScene* scene);

    void simulate_step();

private:
    GameScene*_scene;
    qreal delta_t;
};

#endif // PHYSICSENGINE_H

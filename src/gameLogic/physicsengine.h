#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "scenes/scene.h"

class PhysicsEngine
{
public:
    PhysicsEngine();

    void setScene(Scene* scene);

private:
    Scene *_scene;
};

#endif // PHYSICSENGINE_H

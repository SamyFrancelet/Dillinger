#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "entity.h"

class GameScene : public Scene
{
public:
    GameScene();

    // Scene interface
public:
    void draw(QPainter *p);

    void addEntity(Entity* e);

private:
    QList<Entity*> entities;
};

#endif // GAMESCENE_H

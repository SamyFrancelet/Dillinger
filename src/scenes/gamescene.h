#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "gameObjects/entity.h"

class GameScene : public Scene
{
public:
    GameScene();

    // Scene interface
public:
    void draw(QPainter *p);

    void addEntity(Entity* e);

    QList<Entity*> getEntities();

private:
    QList<Entity*> entities;
};

#endif // GAMESCENE_H

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "gameObjects/entity.h"
#include "gameObjects/player.h"

class GameScene : public Scene
{
public:
    GameScene();

    // Scene interface
public:
    void draw(QPainter *p);

    void addEntity(Entity* e);
    void addPlayer(Player* p);

    QList<Entity*> getEntities();
    Player* getPlayer();

private:
    QList<Entity*> entities;
    Player* _player;
};

#endif // GAMESCENE_H

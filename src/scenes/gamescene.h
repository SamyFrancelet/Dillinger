#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "gameObjects/entity.h"
#include "gameObjects/enemy.h"
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



    const QList<Entity *> &getEntities() const;

    const QList<Watcher *> &getWatchers() const;

    const QList<Enemy *> &getGuards() const;

    Player *getPlayer() const;

private:
    QList<Entity*> entities;
    QList<Watcher*> watchers;
    QList<Enemy*> guards;
    Player* _player;
};

#endif // GAMESCENE_H

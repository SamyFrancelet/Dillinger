#include "gamescene.h"
#include "gameObjects/wall.h"

GameScene::GameScene()
{

}

void GameScene::draw(QPainter *p)
{
    for(Entity* e : entities) {
        e->draw(p);
    }
}

void GameScene::addEntity(Entity *e)
{
    entities.append(e);

    if (e->getName() == "Player") {
        addPlayer(dynamic_cast<Player*>(e));
    }

    if (e->getName() == "Enemy") {
        guards.append(dynamic_cast<Enemy*>(e));
        watchers.append(dynamic_cast<Watcher*>(e));
    }

    if (e->getName() == "CCTV") {
        watchers.append(dynamic_cast<Watcher*>(e));
    }
}

void GameScene::addPlayer(Player *p)
{
    _player = p;
    entities.append(p);
}

const QList<Entity *> &GameScene::getEntities() const
{
    return entities;
}

const QList<Watcher *> &GameScene::getWatchers() const
{
    return watchers;
}

const QList<Enemy *> &GameScene::getGuards() const
{
    return guards;
}

Player *GameScene::getPlayer() const
{
    return _player;
}

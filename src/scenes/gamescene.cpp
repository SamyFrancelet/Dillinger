#include "gamescene.h"
#include "gameObjects/wall.h"

GameScene::GameScene()
{

}

void GameScene::draw(QPainter *p)
{
    for(Entity* e : _entities) {
        e->draw(p);
    }
}

void GameScene::addEntity(Entity *e)
{
    _entities.append(e);

    if (e->getName() == "Player") {
        addPlayer(dynamic_cast<Player*>(e));
    }

    if (e->getName() == "Enemy") {
        _guards.append(dynamic_cast<Enemy*>(e));
        _watchers.append(dynamic_cast<Watcher*>(e));
    }

    if (e->getName() == "CCTV") {
        _watchers.append(dynamic_cast<Watcher*>(e));
    }
}

void GameScene::addPlayer(Player *p)
{
    _player = p;
    _entities.append(p);
}

const QList<Entity *> &GameScene::entities() const
{
    return _entities;
}

const QList<Watcher *> &GameScene::watchers() const
{
    return _watchers;
}

const QList<Enemy *> &GameScene::guards() const
{
    return _guards;
}

Player *GameScene::player() const
{
    return _player;
}

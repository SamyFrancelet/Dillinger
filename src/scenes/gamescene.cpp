#include "gamescene.h"

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
}

void GameScene::addPlayer(Player *p)
{
    _player = p;
    entities.append(p);
}

QList<Entity *> GameScene::getEntities()
{
    return entities;
}

Player *GameScene::getPlayer()
{
    return _player;
}

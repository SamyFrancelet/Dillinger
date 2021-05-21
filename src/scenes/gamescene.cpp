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

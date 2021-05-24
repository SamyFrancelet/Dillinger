#include "gamelogic.h"

#include "gameObjects/dynamicentity.h"

GameLogic::GameLogic()
{
    delta_t = 1;
}

void GameLogic::setScene(GameScene *scene)
{
    _scene = scene;
}

void GameLogic::move_step()
{
    QList<Entity*> entities = _scene->getEntities();

    for(Entity* e : entities) {
        if ( e->getType() == "DynamicEntity" ) { // If the entity is dynamic
            DynamicEntity* d = (DynamicEntity*) e;
            d->moveBy(d->getSpeed() * delta_t);
        }
    }

    _scene->changed();
}

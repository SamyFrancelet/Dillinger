#include "physicsengine.h"

#include "gameObjects/dynamicentity.h"
#include <QDebug>

PhysicsEngine::PhysicsEngine()
{
    delta_t = 2;
}

void PhysicsEngine::setScene(GameScene *scene)
{
    _scene = scene;
}

void PhysicsEngine::simulate_step()
{
    QList<Entity*> entities = _scene->getEntities();

    for(Entity* e : entities) {
        qDebug() << e->getType();
        if ( e->getType() == "DynamicEntity" ) { // If the entity is dynamic
            DynamicEntity* d = (DynamicEntity*) e;
            d->moveBy(d->getSpeed() * delta_t);
        }
    }

    _scene->changed();
}

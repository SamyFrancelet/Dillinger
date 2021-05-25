#include "gamelogic.h"

#include "gameObjects/dynamicentity.h"
#include "gameObjects/staticentity.h"

#include <QDebug>

GameLogic::GameLogic(qreal step_time)
{
    delta_t = step_time;
    moveTimer.setInterval(delta_t);
    moveTimer.start();

    connect(&moveTimer, SIGNAL(timeout()), this, SLOT(move_step()));
}

void GameLogic::setScene(GameScene *scene)
{
    _scene = scene;
}

void GameLogic::move_step()
{
    QList<Entity*> entities = _scene->getEntities();

    for(Entity* e : entities) {
        if (e->getType() == "DynamicEntity")
        { // If the entity is dynamic
            DynamicEntity* d = (DynamicEntity*) e;
            QPointF oldPos = d->pos();
            d->moveBy(d->getSpeed() * delta_t);

            // Collisions out of bound
            if(d->boundingBox().left() < 0 || d->boundingBox().right() > 1280
                    || d->boundingBox().top() < 0 || d->boundingBox().bottom() > 900)
            {
                d->setPos(oldPos);
            }

            // Collisions entity on entity
            for(Entity* others : entities)
            {
                if(others->getType() == "StaticEntity")
                {
                    StaticEntity* statics = (StaticEntity*) others;
                    if(statics->isTangible())
                    {
                        if(d->boundingBox().intersects(statics->boundingBox()))
                        {
                            // When a collision has occured
                            d->setPos(oldPos);
                        }
                    }
                }
            }
        }
    }
    _scene->changed();
}

void GameLogic::keyPressed(int key)
{
    QPointF playerSpeed = _scene->getPlayer()->getSpeed();
    switch (key) {
    case Qt::Key_W:
    //case Qt::Key_Up:
        // GO Up
        playerSpeed.setY(playerSpeed.y()-5);
        break;
    case Qt::Key_A:
    //case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()-5);
        break;
    case Qt::Key_S:
    //case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()+5);
        break;
    case Qt::Key_D:
    //case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()+5);
        break;
    default:
        break;
    }

    _scene->getPlayer()->setSpeed(playerSpeed);
}

void GameLogic::keyReleased(int key)
{
    QPointF playerSpeed = _scene->getPlayer()->getSpeed();
    switch (key) {
    case Qt::Key_W:
    //case Qt::Key_Up:
        // GO Up
        playerSpeed.setY(playerSpeed.y()+5);
        break;
    case Qt::Key_A:
    //case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()+5);
        break;
    case Qt::Key_S:
    //case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()-5);
        break;
    case Qt::Key_D:
    //case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()-5);
        break;
    default:
        break;
    }

    _scene->getPlayer()->setSpeed(playerSpeed);
}

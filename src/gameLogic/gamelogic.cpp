#include "gamelogic.h"

#include "gameObjects/dynamicentity.h"
#include "gameObjects/staticentity.h"

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
        if ( e->getType() == "DynamicEntity" )
        { // If the entity is dynamic
            DynamicEntity* d = (DynamicEntity*) e;
            QPointF oldPos = d->pos();
            d->moveBy(d->getSpeed() * delta_t);
            for(Entity* others : entities)
            {
                if( others->getType() == "StaticEntity")
                {
                    StaticEntity* statics = (StaticEntity*) others;
                    if( statics->isTangible() )
                    {
                        if ( d->boundingBox().intersects(statics->boundingBox()) )
                        {
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
    case Qt::Key_Up:
        // GO Up
        playerSpeed.setY(playerSpeed.y()-10);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()-10);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()+10);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()+10);
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
        playerSpeed.setY(playerSpeed.y()+10);
        break;
    case Qt::Key_A:
    //case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()+10);
        break;
    case Qt::Key_S:
    //case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()-10);
        break;
    case Qt::Key_D:
    //case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()-10);
        break;
    default:
        break;
    }

    _scene->getPlayer()->setSpeed(playerSpeed);
}

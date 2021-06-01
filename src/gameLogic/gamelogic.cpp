#include "gamelogic.h"

#include "gameObjects/dynamicentity.h"
#include "gameObjects/staticentity.h"
#include "gameObjects/enemy.h"

#include <QDebug>

GameLogic::GameLogic(qreal step_time)
{
    delta_t = step_time;
    moveTimer.setInterval(step_time*1000.0);
    moveTimer.start();

    connect(&moveTimer, SIGNAL(timeout()), this, SLOT(game_step()));
}

void GameLogic::setScene(GameScene *scene)
{
    _scene = scene;
}

void GameLogic::keyPressed(int key)
{
    QPointF playerSpeed = _scene->getPlayer()->getSpeed();
    switch (key) {
    case Qt::Key_W:
    //case Qt::Key_Up:
        // GO Up
        playerSpeed.setY(playerSpeed.y()-PLAYER_SPEED);
        break;
    case Qt::Key_A:
    //case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()-PLAYER_SPEED);
        break;
    case Qt::Key_S:
    //case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()+PLAYER_SPEED);
        break;
    case Qt::Key_D:
    //case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()+PLAYER_SPEED);
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
        playerSpeed.setY(playerSpeed.y()+PLAYER_SPEED);
        break;
    case Qt::Key_A:
    //case Qt::Key_Left:
        // GO Left
        playerSpeed.setX(playerSpeed.x()+PLAYER_SPEED);
        break;
    case Qt::Key_S:
    //case Qt::Key_Down:
        // GO Down
        playerSpeed.setY(playerSpeed.y()-PLAYER_SPEED);
        break;
    case Qt::Key_D:
    //case Qt::Key_Right:
        // GO Right
        playerSpeed.setX(playerSpeed.x()-PLAYER_SPEED);
        break;
    default:
        break;
    }

    _scene->getPlayer()->setSpeed(playerSpeed);
}

void GameLogic::mouseClick(QPointF pos)
{

}

void GameLogic::game_step()
{
    playerCatch();
    move_step();
    detections();
}

void GameLogic::playerCatch()
{
    Player* player = _scene->getPlayer();
    if(player != NULL) { // If there is a player
        QList<Enemy*> guards = _scene->getGuards();
        for(Enemy* guard : guards) {
            if (guard->boundingBox().intersects(player->boundingBox())) {
                qDebug() << "Touché !";
            }
        }
    }
}


void GameLogic::detections()
{
    const Player* player = _scene->getPlayer();
    bool detected = false;

    if (player != NULL) {
        QList<QLineF> edges;
        edges.append(QLineF(player->boundingBox().topLeft(), player->boundingBox().topRight()));
        edges.append(QLineF(player->boundingBox().bottomLeft(), player->boundingBox().bottomRight()));
        edges.append(QLineF(player->boundingBox().topLeft(), player->boundingBox().bottomLeft()));
        edges.append(QLineF(player->boundingBox().topRight(), player->boundingBox().bottomRight()));

        const QList<Watcher*> & watchers = _scene->getWatchers();

        for (Watcher* w : watchers) {
            if (QLineF(player->center(), w->viewRays().first()->p1()).length() < CONE_LENGTH + 20) {
                qDebug() << "In range";
                for (QLineF* ray : w->viewRays()) {
                    for (QLineF edge : edges) {
                        if (ray->intersects(edge) == QLineF::BoundedIntersection){
                            detected = true;
                            qDebug() << "Je t'ai vu !";
                        }
                        if(detected) break;
                    }
                    if(detected) break;
                }
            } else {
                //qDebug() << "Too far";
            }
            if(detected) break;
        }

        if (detected) {
            for (Watcher* w : watchers) {
                w->seenAt(player->center());
            }
        }
    }
}

void GameLogic::pathfinding()
{

}

void GameLogic::move_step()
{
    for (Entity* e : _scene->getEntities()) {
        if (e->getType() == "DynamicEntity")
        { // If the entity is dynamic
            DynamicEntity* d = dynamic_cast<DynamicEntity*>(e);
            QPointF oldPos = d->pos();
            d->moveBy(d->getSpeed() * delta_t);

            // Collisions out of bound
            if(d->boundingBox().left() < 0 || d->boundingBox().right() > 1280
                    || d->boundingBox().top() < 0 || d->boundingBox().bottom() > 900)
            {
                d->setPos(oldPos);
            }

            // Collisions entity on entity
            for(Entity* others : _scene->getEntities())
            {
                if(others->getType() == "StaticEntity")
                {
                    StaticEntity* statics = dynamic_cast<StaticEntity*>(others);
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

            // Enemy path following
            if (d->getName() == "Enemy") {
                Enemy* en = dynamic_cast<Enemy*>(d);
                if (!en->path().isEmpty()) { // If the enemy wants to move
                    if (en->getWalking() == false) {
                        QPointF currentPos = en->center();
                        QPointF target = *en->path().first();

                        qreal speedX = target.x() - currentPos.x();
                        qreal speedY = target.y() - currentPos.y();

                        // Scaling to control speed
                        if (abs(speedX) > abs(speedY)) {
                            speedY *= MAX_SPEED/abs(speedX);
                            speedX *= MAX_SPEED/abs(speedX);
                        } else {
                            speedX *= MAX_SPEED/abs(speedY);
                            speedY *= MAX_SPEED/abs(speedY);
                        }
                        en->setSpeed(speedX, speedY);
                        en->setWalking(true);
                    }

                    if (en->boundingBox().contains(*(en->path().first()))) {
                        en->path().removeFirst();
                        en->setWalking(false);
                        en->setSpeed(0,0);
                        if (en->path().isEmpty()) // Juste pour la blague
                            qDebug() << "Oh putain, là je suis bien je bouge plus";
                    }
                } else {
                    en->rotate(1);
                }
            }
        }
    }
    calculateViewRays();
    _scene->changed();
}

void GameLogic::calculateViewRays()
{
    for (Watcher* w : _scene->getWatchers()) {
        for (Entity* e : _scene->getEntities()) {
            if (e->getType() == "StaticEntity") {
                StaticEntity* s = dynamic_cast<StaticEntity*>(e);

                QList<QLineF> edges;
                edges.clear();
                edges.append(QLineF(s->boundingBox().topLeft(), s->boundingBox().topRight()));
                edges.append(QLineF(s->boundingBox().bottomLeft(), s->boundingBox().bottomRight()));
                edges.append(QLineF(s->boundingBox().topLeft(), s->boundingBox().bottomLeft()));
                edges.append(QLineF(s->boundingBox().topRight(), s->boundingBox().bottomRight()));

                for (QLineF* ray : w->viewRays()) {
                    qreal minLength = CONE_LENGTH;
                    for (QLineF edge : edges) {
                        QPointF crossing;
                        if (ray->intersects(edge, &crossing) == QLineF::BoundedIntersection) {
                            qreal length = QLineF(ray->p1(), crossing).length();
                            if (length < minLength) {
                                minLength = length;
                                ray->setP2(crossing);
                            }
                        }
                    }
                }
            }
        }
    }
}

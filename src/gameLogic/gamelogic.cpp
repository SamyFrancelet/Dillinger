#include "gamelogic.h"

#include "gameObjects/dynamicentity.h"
#include "gameObjects/staticentity.h"
#include "gameObjects/enemy.h"

#include <QDebug>

GameLogic::GameLogic(qreal step_time)
{
    delta_t = step_time;
    qreal frame_time = step_time * 1000.0;
    moveTimer.setInterval(frame_time);
    moveTimer.start();

    detectionTimer.setInterval(frame_time * DETECTION_N_FRAME);
    detectionTimer.start();

    connect(&moveTimer, SIGNAL(timeout()), this, SLOT(game_step()));
    connect(&detectionTimer, SIGNAL(timeout()), this, SLOT(detections()));
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
    calculateViewRays();

    _scene->changed();
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
    Watcher* detector = NULL;
    bool detected = false;

    if (player != NULL) {
        QList<QLineF> edges;
        edges.append(QLineF(player->boundingBox().topLeft(), player->boundingBox().topRight()));
        edges.append(QLineF(player->boundingBox().bottomLeft(), player->boundingBox().bottomRight()));
        edges.append(QLineF(player->boundingBox().topLeft(), player->boundingBox().bottomLeft()));
        edges.append(QLineF(player->boundingBox().topRight(), player->boundingBox().bottomRight()));

        for (Watcher* w : _scene->getWatchers()) {
            if (QLineF(player->center(), w->viewRays().first()->p1()).length() < CONE_LENGTH + 20) {
                //qDebug() << "In range";
                for (QLineF* ray : w->viewRays()) {
                    for (QLineF edge : edges) {
                        if (ray->intersects(edge) == QLineF::BoundedIntersection){
                            detected = true;
                            detector = w;
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

        if (detected && QLineF(detector->lastKnownPos(), player->center()).length() > DETECTION_LIMIT) {
            pathfinding();
        }
    }
}

void GameLogic::pathfinding()
{
    // Alert everyone
    for (Watcher* w : _scene->getWatchers()) {
        w->seenAt(_scene->getPlayer()->center());
    }

    QVector<QPoint> notTraversables;

    // Map every point that is not traversable
    for (Entity* e : _scene->getEntities()) {
        if (e->getType() == "StaticEntity") {
            StaticEntity* s = dynamic_cast<StaticEntity*>(e);

            QPoint topLeft = fromSceneToTile(s->boundingBox().topLeft());
            QPoint bottomRight = fromSceneToTile(s->boundingBox().bottomRight());

            for (int x = topLeft.x()-CHAR_SIZE/TILE_SIZE; x < bottomRight.x()+CHAR_SIZE/TILE_SIZE; x++) {
                for (int y = topLeft.y()-CHAR_SIZE/TILE_SIZE; y < bottomRight.y()+CHAR_SIZE/TILE_SIZE; y++) {
                    notTraversables.append(QPoint(x,y));
                }
            }
        }
    }

    for (Enemy* g : _scene->getGuards()) {
        if (QLineF(g->center(), g->lastKnownPos()).length() < VIEW_LENGTH) { // If near enough
            g->clearPath();
            g->addPathStep(new QPointF(g->lastKnownPos()));
        } else { // If too far, need to calculate path
            QVector<Node*> open; // Set of nodes to evaluate
            QVector<Node*> closed; // Set of nodes already evaluated

            Node* startNode = new Node;
            startNode->pos = fromSceneToTile(g->center());
            startNode->cost = 0;
            startNode->parent = NULL;

            Node* endNode;

            open.append(startNode);

            QPoint target = fromSceneToTile(g->lastKnownPos());

            while (!open.isEmpty()) {
                int lowestCost = 10000;
                int nodePos = 0;

                for (int i = 0; i < open.size(); i++) { // Detects node with smallest cost
                    if (open.at(i)->cost < lowestCost) {
                        lowestCost = open.at(i)->cost;
                        nodePos = i;
                    }
                }

                Node* current = open.at(nodePos);
                closed.append(current);
                open.removeAt(nodePos);

                if (current->pos == target) { // Path found
                    endNode = current;
                    break;
                }

                for (int x = current->pos.x()-1; x <= current->pos.x()+1; x++) { // For each neighbour of current
                    for (int y = current->pos.y()-1; y <= current->pos.y()+1; y++) {
                        //-----------------CHECKS IF NEIGHBOUR IS TRAVERSABLE AND ISNT CLOSED---------------
                        if (x < 0 || y < 0)
                            continue; // Skips to next neighbour

                        Node* neighbour = new Node;
                        neighbour->pos = QPoint(x,y);

                        bool isClosed = false;

                        for (Node* n : closed) {
                            if (n->pos == neighbour->pos) {
                                isClosed = true;
                                break;
                            }
                        }

                        if (isClosed)
                            continue; // Skips to next neighbour

                        bool isntTraversable = false;
                        for (QPoint p : notTraversables) {
                            if (p == neighbour->pos) {
                                isntTraversable = true;
                                Node* temp = new Node;
                                temp->parent = NULL;
                                temp->pos = QPoint(x,y);
                                closed.append(temp);
                                break;
                            }
                        }

                        if (isntTraversable)
                            continue; // Skips to next neighbour
                        //-------------------------------------------------------------------------------------

                        // Neighbour is accessible :
                        int currentDist = QLineF(current->pos, target).length();
                        int newDist = QLineF(neighbour->pos, target).length();

                        bool isOpened = false;
                        for (Node* n : open) {
                            if (n->pos == neighbour->pos) {
                                isOpened = true;
                                break;
                            }
                        }

                        if (newDist < currentDist || !isOpened) {
                            int distToOrigin = QLineF(neighbour->pos, startNode->pos).length();
                            neighbour->cost = newDist + distToOrigin;
                            neighbour->parent = current;

                            if (!isOpened)
                                open.append(neighbour);

                        }
                    }
                }
            }

            if (endNode != NULL) {// If a path has been found
                Node* n = endNode;
                qDebug() << "Path found !";
                qDebug() << "I'm here : " << g->center();
                qDebug() << "You are here : " << _scene->getPlayer()->center() << g->lastKnownPos();
                g->clearPath();

                while (n->parent != NULL) {
                    QPointF* step = new QPointF(fromTileToScene(n->pos));
                    qDebug() << *step;
                    g->stackPathStep(step);
                    n = n->parent;
                }
            } else {
                qDebug() << "Path not found...";
            }
        }
    }
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

                    if (en->boundingBox().contains(*(en->path().first()))) {
                        en->path().removeFirst();
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
}

void GameLogic::calculateViewRays()
{
    for (Watcher* w : _scene->getWatchers()) {
        for (Entity* e : _scene->getEntities()) {
            if (e->getType() == "StaticEntity") {
                StaticEntity* s = dynamic_cast<StaticEntity*>(e);

                if (!s->isTransparent()) { // If we can't see through
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
}

QPoint GameLogic::fromSceneToTile(QPointF point)
{
    QPoint tilePoint;
    tilePoint.setX(point.x()/TILE_SIZE);
    tilePoint.setY(point.y()/TILE_SIZE);

    return tilePoint;
}

QPointF GameLogic::fromTileToScene(QPoint point)
{
    QPointF scenePoint;
    scenePoint.setX(point.x()*TILE_SIZE + TILE_SIZE/2);
    scenePoint.setY(point.y()*TILE_SIZE + TILE_SIZE/2);

    return scenePoint;
}

#include "enemy.h"
#include "gameConstants.h"
#include <QDebug>

Enemy::Enemy()
{
    _walking = false;
}

void Enemy::draw(QPainter *p)
{
    p->setPen(QColor(255,255,0,100));
    for(QLineF* ray : viewRays())
    {
        p->drawLine(*ray);
    }

    Entity::draw(p);

    p->setPen(QColor(0,0,0,255));
    p->setBrush(QColor(255,0,0));
    p->drawEllipse(boundingBox());
}

QString Enemy::getName() const
{
    return "Enemy";
}

void Enemy::setPos(QPointF newPos)
{
    Entity::setPos(newPos);
    Watcher::setPos(boundingBox().center());
}

void Enemy::setPos(qreal x, qreal y)
{
    Entity::setPos(x,y);
    Watcher::setPos(boundingBox().center().x(), boundingBox().center().y());
}

void Enemy::moveBy(QPointF delta_pos)
{
    Entity::moveBy(delta_pos);
    Watcher::moveBy(delta_pos);
}

void Enemy::moveBy(qreal x, qreal y)
{
    Entity::moveBy(x,y);
    Watcher::moveBy(x,y);
}

void Enemy::setSpeed(QPointF speed)
{
    DynamicEntity::setSpeed(speed);
    if (speed != QPointF(0,0)) {
        QLineF direction(QPointF(0,0), speed);
        setAngle(direction.angle());
    }
}

void Enemy::setSpeed(qreal x, qreal y)
{
    DynamicEntity::setSpeed(x,y);
    if (x != 0.0 || y != 0.0) {
        QLineF direction(QPointF(0,0), QPointF(x,y));
        setAngle(direction.angle());
    }
}

void Enemy::seenAt(QPointF pos)
{
    Watcher::seenAt(pos);

    QVector<Node*> open;
    QVector<Node*> closed;

    Node* startNode = new Node;
    startNode->pos = fromSceneToTile(this.pos());
    startNode->cost = 0;

    open.append(startNode);

    while(true) {
        int lowestCost = 100;
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

        if (current->pos == fromSceneToTile(*lastKnownPos()))
            break; // Path has been found

        // J'ai plus la monstre envie là de suite, faut bouger cette méthode dans le contrôleur
        // Parce qu'il faut savoir ou sont les murs...
    }
}

QVector<QPointF*> &Enemy::path()
{
    return _path;
}

bool Enemy::getWalking() const
{
    return _walking;
}

void Enemy::setWalking(bool walking)
{
    _walking = walking;
}

void Enemy::addPathStep(QPointF *target)
{
    _path.append(target);
}

QPoint Enemy::fromSceneToTile(QPointF point)
{
    QPoint tilePoint;
    tilePoint.setX(point.x()/TILE_SIZE + TILE_SIZE/2);
    tilePoint.setY(point.y()/TILE_SIZE + TILE_SIZE/2);

    return tilePoint;
}

#include "enemy.h"

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

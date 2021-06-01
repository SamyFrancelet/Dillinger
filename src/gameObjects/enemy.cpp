#include "enemy.h"

Enemy::Enemy()
{

}

void Enemy::draw(QPainter *p)
{
    /*p->setPen(QColor(0,0,0,0));
    p->setBrush(QColor(255,255,0, 50));
    p->drawPolygon(viewCone());*/

    p->setPen(QColor(255,255,0,100));
    for(QLineF* ray : viewRays())
    {
        p->drawLine(*ray);
    }

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

#include "entity.h"


void Entity::draw(QPainter *p)
{
    p->drawEllipse(_pos, 100, 100);
}

QPoint Entity::pos() const
{
    return _pos;
}

void Entity::setPos(QPoint newPos)
{
    _pos = newPos;
}

void Entity::setPos(int x, int y)
{
    _pos.setX(x);
    _pos.setY(y);
}

qreal Entity::angle() const
{
    return _angle;
}

void Entity::setAngle(qreal newAngle)
{
    _angle = newAngle;
}

const QRect &Entity::boundingBox() const
{
    return _boundingBox;
}

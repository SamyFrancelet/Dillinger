#include "entity.h"

Entity::Entity(qreal width, qreal height)
{
    _boundingBox.setWidth(width);
    _boundingBox.setHeight(height);
    _boundingBox.moveTo(0,0);
}

QPointF Entity::pos() const
{
    return _boundingBox.topLeft();
}

void Entity::setPos(QPointF newPos)
{
    _boundingBox.moveTo(newPos);
}

void Entity::setPos(qreal x, qreal y)
{
    _boundingBox.moveTo(x,y);
}

void Entity::moveBy(QPointF delta_pos)
{
    _boundingBox.translate(delta_pos);
}

void Entity::moveBy(qreal x, qreal y)
{
    _boundingBox.translate(x,y);
}

QString Entity::getType() const
{
    return "Entity";
}

const QRectF &Entity::boundingBox() const
{
    return _boundingBox;
}

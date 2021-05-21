#include "entity.h"


/*Entity::Entity()
{
    _actualSprite = new QPixmap(":/sprites/snoopyR.png");
    _sprites.append(_actualSprite);
}*/

void Entity::draw(QPainter *p)
{
    p->drawPixmap(this->pos(), *_actualSprite);
}

QPointF Entity::pos() const
{
    return _boundingBox.topLeft();
}

void Entity::setPos(QPointF newPos)
{
    _boundingBox.setTopLeft(newPos);
}

void Entity::setPos(qreal x, qreal y)
{
    _boundingBox.setTopLeft(QPointF(x,y));
}

orientation Entity::angle() const
{
    return _angle;
}

void Entity::setAngle(orientation newAngle)
{
    _angle = newAngle;
}

const QRectF &Entity::boundingBox() const
{
    return _boundingBox;
}

#include "entity.h"

Entity::Entity(qreal width, qreal height)
{
    _boundingBox.setWidth(width);
    _boundingBox.setHeight(height);
    _boundingBox.moveTo(0,0);

    _actualSprite = new QPixmap(":/sprites/snoopyR.png");
    _sprites.append(_actualSprite);

    _angle = 0;
}

void Entity::draw(QPainter *p)
{
    QTransform tr;
    tr.rotate(_angle);
    QPixmap temp = _actualSprite->transformed(tr);
    p->drawPixmap(pos(), temp);
    p->drawRect(_boundingBox);
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

qreal Entity::angle() const
{
    return _angle;
}

void Entity::setAngle(qreal newAngle)
{
    _angle = newAngle;
}

QString Entity::getType() const
{
    return "Entity";
}

const QRectF &Entity::boundingBox() const
{
    return _boundingBox;
}

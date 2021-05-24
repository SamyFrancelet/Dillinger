#include "dynamicentity.h"

DynamicEntity::DynamicEntity() : Entity(100,100)
{
    _actualSprite = new QPixmap(":/sprites/snoopyR.png");
    _sprites.append(_actualSprite);
}

void DynamicEntity::setSpeed(QPointF speed)
{
    _speed = speed;
}

void DynamicEntity::setSpeed(qreal x, qreal y)
{
    _speed.setX(x);
    _speed.setY(y);
}

QPointF DynamicEntity::getSpeed()
{
    return _speed;
}

QString DynamicEntity::getType() const
{
    return "DynamicEntity";
}

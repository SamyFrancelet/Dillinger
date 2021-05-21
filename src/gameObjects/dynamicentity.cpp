#include "dynamicentity.h"

DynamicEntity::DynamicEntity()
{
    _actualSprite = new QPixmap(":/sprites/snoopyR.png");
    _sprites.append(_actualSprite);
}

/*void DynamicEntity::updatePos(qreal delta_t)
{
    QPointF delta_pos;
    delta_pos.setX(0);
    delta_pos.setY(0);

    switch (angle()) {
    case UP:
        delta_pos.setY(delta_t*_speed);
        break;
    case DOWN:
        delta_pos.setY(-delta_t*_speed);
        break;
    case LEFT:
        delta_pos.setX(-delta_t*_speed);
        break;
    case RIGHT:
        delta_pos.setX(delta_t*_speed);
        break;
    case UP_LEFT:
        delta_pos.setX(-0.707*delta_t*_speed);
        delta_pos.setY(0.707*delta_t*_speed);
        break;
    case UP_RIGHT:
        delta_pos.setX(0.707*delta_t*_speed);
        delta_pos.setY(0.707*delta_t*_speed);
        break;
    case DOWN_LEFT:
        delta_pos.setX(-0.707*delta_t*_speed);
        delta_pos.setY(-0.707*delta_t*_speed);
        break;
    case DOWN_RIGHT:
        delta_pos.setX(0.707*delta_t*_speed);
        delta_pos.setY(-0.707*delta_t*_speed);
        break;
    default:
        break;
    }

    setPos(pos() + delta_pos);
}*/

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

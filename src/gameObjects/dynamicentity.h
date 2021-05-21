#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

class DynamicEntity : public Entity
{
public:
    DynamicEntity();

    void setSpeed(QPointF speed);
    void setSpeed(qreal x, qreal y);

    QPointF getSpeed();

private:
    QPointF _speed;
};

#endif // DYNAMICENTITY_H

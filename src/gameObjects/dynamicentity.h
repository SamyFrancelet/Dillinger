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

    // Entity interface
public:
    QString getType() const;
};

#endif // DYNAMICENTITY_H

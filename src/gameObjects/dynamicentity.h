#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

/**
 * @brief The DynamicEntity class, represent a moving object
 */
class DynamicEntity : public Entity
{
public:
    DynamicEntity(qreal width, qreal height);

    virtual void setSpeed(QPointF speed);
    virtual void setSpeed(qreal x, qreal y);

    QPointF getSpeed();

private:
    QPointF _speed;

    // Entity interface
public:
    QString getType() const;
};

#endif // DYNAMICENTITY_H

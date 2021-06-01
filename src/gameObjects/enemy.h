#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "watcher.h"

class Enemy : public Watcher, public Character
{
public:
    Enemy();

    // Entity interface
public:
    void draw(QPainter *p);

    QString getName() const;

    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);
};

#endif // ENEMY_H

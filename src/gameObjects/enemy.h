#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "watcher.h"

#include <QVector>

#define MAX_SPEED 200.0

class Enemy : public Character, public Watcher
{
public:
    Enemy();

    QVector<QPointF*> &path();

    bool getWalking() const;
    void setWalking(bool walking);

    void addPathStep(QPointF* target);

    // Entity interface
public:
    void draw(QPainter *p);

    QString getName() const;

    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);

    // DynamicEntity interface
public:
    void setSpeed(QPointF speed);
    void setSpeed(qreal x, qreal y);

private:
    QVector<QPointF*> _path;
    bool _walking;
};

#endif // ENEMY_H

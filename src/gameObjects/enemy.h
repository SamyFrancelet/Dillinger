#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "watcher.h"

#include <QVector>

/**
 * @brief The Enemy class, represent either a cop or a guard
 */
class Enemy : public Character, public Watcher
{
public:
    Enemy();

    /**
     * @brief path to follow
     * @return a Vector array with each point to follow
     */
    QVector<QPointF*> &path();

    void clearPath();
    void addPathStep(QPointF* step);
    void stackPathStep(QPointF* step);

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
};

#endif // ENEMY_H

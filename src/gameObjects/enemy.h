#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "watcher.h"

#include <QVector>

#define MAX_SPEED 100.0

struct Node
{
    QPoint pos;
    int cost;
};

class Enemy : public Character, public Watcher
{
public:
    Enemy();

    QVector<QPointF*> &path();

    bool getWalking() const;
    void setWalking(bool walking);

    void addPathStep(QPointF* target);

    QPoint fromSceneToTile(QPointF point);
    QPointF fromTileToScene(QPoint point);

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

    // Watcher interface
public:
    void seenAt(QPointF pos);
};

#endif // ENEMY_H

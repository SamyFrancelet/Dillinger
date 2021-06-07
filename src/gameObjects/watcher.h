#ifndef WATCHER_H
#define WATCHER_H

#include "gameConstants.h"

#include <QLineF>
#include <QPoint>
#include <QPolygon>

/**
 * @brief The Watcher class, represent an object that can see the player
 */
class Watcher
{
public:
    Watcher();
    ~Watcher();

    virtual void seenAt(QPointF pos);

    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);

    void setAngle(qreal angle);
    void rotate(qreal angle);

    /**
     * @brief lastKnownPos of the player
     * @return the last coordinate where the player was seen
     */
    QPointF lastKnownPos() const;

    /**
     * @brief all view Rays of the Watcher
     * @return A list of every Line representing a view ray
     */
    const QList<QLineF *> &viewRays() const;

private:
    QPointF* _lastKnownPos;
    QList<QLineF*> _viewRays;
    qreal _angle;

    void generateViewRays(QPointF origin);
};

#endif // WATCHER_H

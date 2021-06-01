#ifndef WATCHER_H
#define WATCHER_H

#include <QLineF>
#include <QPoint>
#include <QPolygon>

#define CONE_LENGTH 200.0
#define CONE_WIDTH 100.0
#define CONE_ANGLE 70.0
#define N_RAYS 150 // Number of rays (minus the central ray)

class Watcher
{
public:
    Watcher();
    ~Watcher();

    void seenAt(QPointF pos);

    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);

    void setAngle(qreal angle);
    void rotate(qreal angle);

    QPointF *lastKnownPos() const;

    const QList<QLineF *> &viewRays() const;

private:
    QPointF* _lastKnownPos;
    QList<QLineF*> _viewRays;
    qreal _angle;

    void generateViewRays(QPointF origin);
};

#endif // WATCHER_H

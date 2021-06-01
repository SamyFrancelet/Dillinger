#include "watcher.h"

#include <QtMath>
#include <QDebug>

Watcher::Watcher()
{
    _lastKnownPos = NULL;

    _angle = (0.0/180.0) * M_PI;

    QPointF centerPoint(CONE_LENGTH*qCos(_angle), -CONE_LENGTH*qSin(_angle));
    QPointF shift((CONE_WIDTH/2)*qSin(_angle), (CONE_WIDTH/2)*qCos(_angle));
    QPointF origin(0,0);

    _viewCone << origin;
    _viewCone << centerPoint + shift;
    _viewCone << centerPoint - shift;

    for(int i = 0; i <= N_RAYS; i++)
    {
        QLineF* temp;;
        qreal shiftAngle = ((CONE_ANGLE/180.0) * M_PI) * (i-N_RAYS/2.0)/N_RAYS;
        QPointF extremity(CONE_LENGTH*qCos(_angle + shiftAngle), -CONE_LENGTH*qSin(_angle + shiftAngle));
        temp = new QLineF(origin, extremity);
        _viewRays.append(temp);
    }
}

Watcher::~Watcher()
{
    delete _lastKnownPos;
}

void Watcher::seenAt(QPointF pos)
{
    delete _lastKnownPos;
    _lastKnownPos = new QPointF(pos);
}

void Watcher::setPos(QPointF newPos)
{
    QPolygonF newCone;

    QPointF centerPoint(CONE_LENGTH*qCos(_angle), -CONE_LENGTH*qSin(_angle));
    QPointF shift((CONE_WIDTH/2)*qSin(_angle), (CONE_WIDTH/2)*qCos(_angle));

    newCone << newPos;
    newCone << centerPoint + shift + newPos;
    newCone << centerPoint - shift + newPos;

    _viewCone = newCone;

    _viewRays.clear();
    for(int i = 0; i <= N_RAYS; i++)
    {
        QLineF* temp;
        qreal shiftAngle = ((CONE_ANGLE/180.0) * M_PI) * (i-N_RAYS/2.0)/N_RAYS;
        QPointF extremity(CONE_LENGTH*qCos(_angle + shiftAngle), -CONE_LENGTH*qSin(_angle + shiftAngle));
        temp = new QLineF(newPos, extremity + newPos);
        _viewRays.append(temp);
    }
}

void Watcher::setPos(qreal x, qreal y)
{
    QPolygonF newCone;
    QPointF newPos(x,y);

    QPointF centerPoint(CONE_LENGTH*qCos(_angle), -CONE_LENGTH*qSin(_angle));
    QPointF shift((CONE_WIDTH/2)*qSin(_angle), (CONE_WIDTH/2)*qCos(_angle));

    newCone << newPos;
    newCone << centerPoint + shift + newPos;
    newCone << centerPoint - shift + newPos;

    _viewCone = newCone;

    _viewRays.clear();
    for(int i = 0; i <= N_RAYS; i++)
    {
        QLineF* temp;
        qreal shiftAngle = ((CONE_ANGLE/180.0) * M_PI) * (i-N_RAYS/2.0)/N_RAYS;
        QPointF extremity(CONE_LENGTH*qCos(_angle + shiftAngle), -CONE_LENGTH*qSin(_angle + shiftAngle));
        temp = new QLineF(newPos, extremity + newPos);
        _viewRays.append(temp);
    }
}

void Watcher::moveBy(QPointF delta_pos)
{
    _viewCone.translate(delta_pos);
}

void Watcher::moveBy(qreal x, qreal y)
{
    _viewCone.translate(x,y);
}

void Watcher::setAngle(qreal angle)
{
    _angle = (angle/180.0) * M_PI;

    QPointF currentPos = _viewCone.constFirst();
    QPolygonF newCone;

    QPointF centerPoint(CONE_LENGTH*qCos(_angle), -CONE_LENGTH*qSin(_angle));
    QPointF shift((CONE_WIDTH/2)*qSin(_angle), (CONE_WIDTH/2)*qCos(_angle));

    newCone << currentPos;
    newCone << centerPoint + shift + currentPos;
    newCone << centerPoint - shift + currentPos;

    _viewCone = newCone;

    _viewRays.clear();
    for(int i = 0; i <= N_RAYS; i++)
    {
        QLineF* temp;
        qreal shiftAngle = ((CONE_ANGLE/180.0) * M_PI) * (i-N_RAYS/2.0)/N_RAYS;
        QPointF extremity(CONE_LENGTH*qCos(_angle + shiftAngle), -CONE_LENGTH*qSin(_angle + shiftAngle));
        temp = new QLineF(currentPos, extremity + currentPos);
        _viewRays.append(temp);
    }
}

void Watcher::cutViewCone(const QPolygonF cutter)
{
    _viewCone = _viewCone.subtracted(cutter);
    qDebug() << _viewCone;
}

const QPolygonF &Watcher::viewCone() const
{
    return _viewCone;
}

QPointF *Watcher::lastKnownPos() const
{
    return _lastKnownPos;
}

const QList<QLineF *> &Watcher::viewRays() const
{
    return _viewRays;
}

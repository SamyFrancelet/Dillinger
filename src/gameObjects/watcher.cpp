#include "watcher.h"

#include <QtMath>
#include <QDebug>

Watcher::Watcher()
{
    _lastKnownPos = new QPointF(-100.0,-100.0);

    _angle = 0.0;

    generateViewRays(QPointF(0,0));
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
    generateViewRays(newPos);
}

void Watcher::setPos(qreal x, qreal y)
{
    generateViewRays(QPointF(x,y));
}

void Watcher::moveBy(QPointF delta_pos)
{
    QPointF currentPos = _viewRays.first()->p1();
    currentPos += delta_pos;
    generateViewRays(currentPos);
}

void Watcher::moveBy(qreal x, qreal y)
{
    QPointF currentPos = _viewRays.first()->p1();
    currentPos += QPointF(x,y);
    generateViewRays(currentPos);
}

void Watcher::setAngle(qreal angle)
{
    _angle = angle;

    QPointF currentPos = _viewRays.first()->p1(); // Gets origin Point
    generateViewRays(currentPos);
}

void Watcher::rotate(qreal angle)
{
    _angle += angle;

    QPointF currentPos = _viewRays.first()->p1(); // Gets origin Point
    generateViewRays(currentPos);
}

QPointF Watcher::lastKnownPos() const
{
    return *_lastKnownPos;
}

const QList<QLineF *> &Watcher::viewRays() const
{
    return _viewRays;
}

void Watcher::generateViewRays(QPointF origin)
{
    _viewRays.clear();
    for(int i = -N_RAYS/2; i <= N_RAYS/2; i++)
    {
        QLineF* temp;
        qreal shiftAngle = VIEW_ANGLE * (i)/(N_RAYS);
        QPointF extremity(VIEW_LENGTH, 0);
        temp = new QLineF(origin, extremity + origin);
        temp->setAngle(_angle + shiftAngle);
        _viewRays.append(temp);
    }
}

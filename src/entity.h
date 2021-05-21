#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>
#include <QPoint>

class Entity
{
public:
    void draw(QPainter* p);

    QPoint pos() const;
    void setPos(QPoint newPos);
    void setPos(int x, int y);

    qreal angle() const;
    void setAngle(qreal newAngle);

    const QRect &boundingBox() const;

private:
    QPoint _pos;
    qreal _angle;
    QRect _boundingBox;
};

#endif // ENTITY_H

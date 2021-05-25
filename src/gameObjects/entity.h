#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>
#include <QPoint>

class Entity
{
public:
    Entity(qreal width, qreal height);

    virtual void draw(QPainter* p) = 0;

    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);

    QPointF pos() const;
    const QRectF &boundingBox() const;
    virtual QString getType() const;

private:
    QRectF _boundingBox;
};

#endif // ENTITY_H

#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>
#include <QPoint>

#define DRAW_BOUNDINGBOXES false

class Entity
{
public:
    Entity(qreal width, qreal height);

    virtual void draw(QPainter* p);

    virtual void setPos(QPointF newPos);
    virtual void setPos(qreal x, qreal y);

    virtual void moveBy(QPointF delta_pos);
    virtual void moveBy(qreal x, qreal y);

    QPointF pos() const;
    QPointF center() const;
    const QRectF &boundingBox() const;
    virtual QString getType() const;
    virtual QString getName() const = 0;

private:
    QRectF _boundingBox;
};

#endif // ENTITY_H

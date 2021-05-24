#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>
#include <QPoint>

enum orientation { UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

class Entity
{
public:
    Entity(qreal width, qreal height);

    void draw(QPainter* p);

    const QRectF &boundingBox() const;

    QPointF pos() const;
    void setPos(QPointF newPos);
    void setPos(qreal x, qreal y);

    void moveBy(QPointF delta_pos);
    void moveBy(qreal x, qreal y);

    orientation angle() const;
    void setAngle(orientation newAngle);

    virtual QString getType() const;

protected:
    QList<QPixmap*> _sprites;
    QPixmap* _actualSprite;

private:
    orientation _angle;
    QRectF _boundingBox;
};

#endif // ENTITY_H

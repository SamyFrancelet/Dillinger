#include "wall.h"

Wall::Wall(qreal width, qreal height)
    : StaticEntity(width, height)
{
    _isTransparent = false;
    _isNoiseMuffler = true;
    _isTangible = true;
}

void Wall::draw(QPainter *p)
{
    p->setPen(QColor(0,0,0,0));
    p->setBrush(Qt::Dense7Pattern);
    p->drawRect(boundingBox());
}

QString Wall::getName() const
{
    return "Wall";
}

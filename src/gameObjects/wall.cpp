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
    p->setBrush(Qt::Dense2Pattern);
    p->drawRect(boundingBox());
}

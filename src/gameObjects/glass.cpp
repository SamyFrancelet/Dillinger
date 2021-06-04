#include "glass.h"

Glass::Glass(qreal width, qreal height)
    : StaticEntity(width, height)
{
    _isTransparent = true;
    _isNoiseMuffler = true;
    _isTangible = true;
}

void Glass::draw(QPainter* p)
{
    p->setPen(QColor(0,0,0,0));
    p->setBrush(Qt::Dense6Pattern);
    p->drawRect(boundingBox());
}

QString Glass::getName() const
{
    return "Glass";
}

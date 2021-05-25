#include "wall.h"

Wall::Wall(qreal width, qreal height)
    : StaticEntity(width, height)
{

}

void Wall::draw(QPainter *p)
{
    p->setBrush(Qt::Dense1Pattern);
    p->drawRect(boundingBox());
}

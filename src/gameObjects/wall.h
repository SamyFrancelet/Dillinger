#ifndef WALL_H
#define WALL_H

#include "staticentity.h"

class Wall : public StaticEntity
{
public:
    Wall(qreal width, qreal height);

    // Entity interface
public:
    void draw(QPainter *p);
};

#endif // WALL_H

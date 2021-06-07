#ifndef WALL_H
#define WALL_H

#include "staticentity.h"

/**
 * @brief The Wall class, can not be seen through
 */
class Wall : public StaticEntity
{
public:
    Wall(qreal width, qreal height);

    // Entity interface
public:
    void draw(QPainter *p);
    QString getName() const;
};

#endif // WALL_H

#ifndef GLASS_H
#define GLASS_H

#include "staticentity.h"

class Glass : public StaticEntity
{
public:
    Glass(qreal width, qreal height);

    // Entity interface
public:
    void draw(QPainter *p);
    QString getName() const;
};

#endif // GLASS_H

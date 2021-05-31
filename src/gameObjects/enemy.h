#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
public:
    Enemy();

    // Entity interface
public:
    void draw(QPainter *p);
};

#endif // ENEMY_H

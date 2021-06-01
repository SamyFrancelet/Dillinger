#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character
{
public:
    Player();

    // Entity interface
public:
    void draw(QPainter *p);

    QString getName() const;
};

#endif // PLAYER_H

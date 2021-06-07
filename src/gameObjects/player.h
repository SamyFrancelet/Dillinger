#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

/**
 * @brief The Player class, controlled with the keyboard
 */
class Player : public Character
{
public:
    Player();

	bool caught();
	void gotCaught();

    // Entity interface
public:
    void draw(QPainter *p);

    QString getName() const;

private:
	bool _caught;
};

#endif // PLAYER_H

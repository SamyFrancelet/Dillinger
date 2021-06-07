#include "player.h"

Player::Player()
{
    _caught = false;
}

bool Player::caught()
{
	return _caught;
}

void Player::gotCaught()
{
	_caught = true;
}

void Player::draw(QPainter *p)
{
    Entity::draw(p);

    p->setBrush(QColor(0,255,0));
    p->drawEllipse(boundingBox());
}

QString Player::getName() const
{
    return "Player";
}

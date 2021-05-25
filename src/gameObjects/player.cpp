#include "player.h"

Player::Player()
{

}

void Player::draw(QPainter *p)
{
    p->setBrush(QColor(255,0,0));
    p->drawEllipse(boundingBox());
}

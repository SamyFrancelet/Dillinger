#include "player.h"

Player::Player()
{

}

void Player::draw(QPainter *p)
{
    p->setBrush(QColor(0,255,0));
    p->drawEllipse(boundingBox());
}

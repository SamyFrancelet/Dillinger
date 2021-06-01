#include "player.h"

Player::Player()
{

}

void Player::draw(QPainter *p)
{
    p->setPen(QColor(0,0,0,255));
    p->setBrush(QColor(0,255,0));
    p->drawEllipse(boundingBox());
}

QString Player::getName() const
{
    return "Player";
}

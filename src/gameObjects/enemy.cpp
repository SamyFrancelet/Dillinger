#include "enemy.h"

Enemy::Enemy()
{

}

void Enemy::draw(QPainter *p)
{
    p->setBrush(QColor(255,0,0));
    p->drawEllipse(boundingBox());
}

#include "staticentity.h"

StaticEntity::StaticEntity(qreal width, qreal height)
    : Entity(width, height)
{

}

bool StaticEntity::isTangible() const
{
    return _isTangible;
}

bool StaticEntity::isNoiseMuffler() const
{
    return _isNoiseMuffler;
}

bool StaticEntity::isTransparent() const
{
    return _isTransparent;
}

QString StaticEntity::getType() const
{
    return "StaticEntity";
}

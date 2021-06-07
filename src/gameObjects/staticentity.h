#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "entity.h"

/**
 * @brief The StaticEntity class, represents every non-moving objects
 */
class StaticEntity : public Entity
{
public:
    StaticEntity(qreal width, qreal height);	
    bool isTransparent() const;
    bool isNoiseMuffler() const;
    bool isTangible() const;

protected:
    bool _isTransparent;
    bool _isNoiseMuffler;
    bool _isTangible;

    // Entity interface
public:
    QString getType() const;
};

#endif // STATICENTITY_H

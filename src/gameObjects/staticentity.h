#ifndef STATICENTITY_H
#define STATICENTITY_H

#include "entity.h"

class StaticEntity : public Entity
{
public:
    StaticEntity(qreal width, qreal height);	

private:
	bool isTransparent;
	bool isNoiseMuffler;
	bool isTangible;
};

#endif // STATICENTITY_H

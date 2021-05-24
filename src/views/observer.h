#ifndef OBSERVER_H
#define OBSERVER_H

#include "scenes/scene.h"¨

class Observer
{
public:
    virtual void refresh() = 0;
    virtual void stop() = 0;

    void setScene(Scene* s)
    {
        _s = s;
        _s->subscribe(this);
    }

protected:
    Scene* _s;
};

#endif // OBSERVER_H

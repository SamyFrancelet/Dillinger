#ifndef OBSERVER_H
#define OBSERVER_H

class Scene;


class Observer
{
public:
    virtual void refresh() = 0;
    virtual void stop() = 0;

    void setScene(Scene* s) { _s = s; }

protected:
    Scene* _s;
};

#endif // OBSERVER_H

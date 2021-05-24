#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <QPainter>

class Observer;

class Scene
{
public:
    void changed();
    void subscribe(Observer* obs);

    virtual void draw(QPainter* p) = 0;

protected:
    QList<Observer*> _observers;
};

#endif // SCENE_H
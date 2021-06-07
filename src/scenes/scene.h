#ifndef SCENE_H
#define SCENE_H

#include <QList>
#include <QPainter>

class Observer;

/**
 * @brief The Scene abstract class, model that can be drawn on a widget
 */
class Scene
{
public:
    void changed();

    /**
     * @brief subscribe an observer to alert when the scene has changes
     * @param obs, the observer to subscribe
     */
    void subscribe(Observer* obs);

    virtual void draw(QPainter* p) = 0;

protected:
    QList<Observer*> _observers;
};

#endif // SCENE_H

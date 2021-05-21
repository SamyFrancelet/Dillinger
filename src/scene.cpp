#include "scene.h"


void Scene::changed()
{
    for(Observer* obs : _observers) {
        obs->refresh();
    }
}

void Scene::subscribe(Observer *obs)
{
    _observers.append(obs);
}

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "gameObjects/entity.h"
#include "gameObjects/enemy.h"
#include "gameObjects/player.h"

/**
 * @brief The GameScene class, model containing every game objects to draw
 */
class GameScene : public Scene
{
public:
    GameScene();

    // Scene interface
public:
    /**
     * @brief draw every game entities
     * @param p, the widget painter
     */
    void draw(QPainter *p);

    void addEntity(Entity* e);
    void addPlayer(Player* p);

    const QList<Entity *> &entities() const;

    const QList<Watcher *> &watchers() const;

    const QList<Enemy *> &guards() const;

    Player *player() const;

private:
    QList<Entity*> _entities;
    QList<Watcher*> _watchers;
    QList<Enemy*> _guards;
    Player* _player;
};

#endif // GAMESCENE_H

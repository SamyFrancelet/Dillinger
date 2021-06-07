#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "scenes/gamescene.h"
#include "controller.h"
#include "gameConstants.h"
#include <QTimer>

/**
 * @brief The Node struct, represents a pathfinding node
 */
struct Node
{
    QPoint pos;
    int cost;

    Node* parent;
};

/**
 * @brief The GameLogic controller class
 * Has every method to control the Dillinger game
 */
class GameLogic : public QObject, public Controller
{
    Q_OBJECT
public:
    /**
     * @brief GameLogic constructor
     * @param delta_t frame time in sec, also used to calculate physics
     */
    GameLogic(qreal delta_t);

    /**
     * @brief setScene to control
     * @param scene
     */
    void setScene(GameScene* scene);

private slots:
    /**
     * @brief game_step, calls every method needed each frame
     */
    void game_step();

    /**
     * @brief calculate enemy detections
     */
    void detections();

private:
    /**
     * @brief gameOver, self-explaining
     */
	void gameOver();

    /**
     * @brief check if an enemy has caught the player
     */
    void playerCatch();

    /**
     * @brief calculate pathfinding to player for every enemy
     */
    void pathfinding();

    /**
     * @brief physical move step of every dynamic entity
     */
    void move_step();

    /**
     * @brief calculateViewRays from every watcher
     */
    void calculateViewRays();

    /**
     * @brief convert scene coordinate to pathfinding tile coordinate
     * @param point from scene coordinate
     * @return point from tile coordinate
     */
    QPoint fromSceneToTile(QPointF point);


    /**
     * @brief convert pathfinding tile to scene coordinate coordinate
     * @param point from tile coordinate
     * @return point from scene coordinate
     */
    QPointF fromTileToScene(QPoint point);

    GameScene* _scene;
    qreal delta_t;
    QTimer moveTimer;
    QTimer detectionTimer;

    // Controller interface
public:
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseClick(QPointF pos);
};

#endif // GAMELOGIC_H

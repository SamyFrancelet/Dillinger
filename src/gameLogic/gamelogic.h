#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "scenes/gamescene.h"
#include "controller.h"
#include "gameConstants.h"
#include <QTimer>

struct Node
{
    QPoint pos;
    int cost;

    Node* parent;
};

class GameLogic : public QObject, public Controller
{
    Q_OBJECT
public:
    GameLogic(qreal delta_t);

    void setScene(GameScene* scene);

private slots:
    void game_step();
    void detections();

private:
    void playerCatch();
    void pathfinding();
    void move_step();

    void calculateViewRays();

    QPoint fromSceneToTile(QPointF point);
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

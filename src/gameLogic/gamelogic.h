#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "scenes/gamescene.h"
#include "controller.h"
#include <QTimer>

class GameLogic : public QObject, public Controller
{
    Q_OBJECT
public:
    GameLogic(qreal delta_t);

    void setScene(GameScene* scene);

private slots:
    void game_step();

private:
    void detections();
    void move_step();

    GameScene* _scene;
    qreal delta_t;
    QTimer moveTimer;
};

#endif // GAMELOGIC_H

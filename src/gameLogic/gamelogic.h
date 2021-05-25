#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "scenes/gamescene.h"
#include <QTimer>

class GameLogic : public QObject
{
    Q_OBJECT
public:
    GameLogic(qreal delta_t);

    void setScene(GameScene* scene);

    void keyPressed(int key);
    void keyReleased(int key);

private slots:
    void move_step();

private:
    GameScene* _scene;
    qreal delta_t;
    QTimer moveTimer;
};

#endif // GAMELOGIC_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

class QPointF;

/**
 * @brief The Controller interface
 * Represents a controller, that receives keyPresses and mousClick
 * from a Qt Widget
 */
class Controller
{
public:
    virtual void keyPressed(int key) = 0;
    virtual void keyReleased(int key) = 0;

    virtual void mouseClick(QPointF pos) = 0;
};

#endif // CONTROLLER_H

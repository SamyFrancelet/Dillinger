#ifndef CONTROLLER_H
#define CONTROLLER_H

class QPointF;

class Controller
{
public:
    virtual void keyPressed(int key) = 0;
    virtual void keyReleased(int key) = 0;

    virtual void mouseClick(QPointF pos) = 0;
};

#endif // CONTROLLER_H

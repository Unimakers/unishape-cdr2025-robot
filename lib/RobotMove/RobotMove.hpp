#pragma once
#include "ROBOT_VARIABLES.h"
#include <AccelStepper.h>

#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H
#endif

typedef struct
{
    int x;
    int y;
    float angle;
} Coord;

typedef struct
{
    int left;
    int right;
} ActionDistance;

enum struct MoveToState
{
    INACTIVE,
    FIRST_TURN,
    MOVE,
    LAST_TURN
};
typedef struct
{
    MoveToState step;
    int speed;// current step
    Coord target; // the target
}ActionMoveTo;
class RobotMove
{
protected:
    AccelStepper left, right;

    ActionDistance currentAction;
    ActionMoveTo currentActionMoveTo;
    bool paused = true;

public:
    Coord currentPos;
    bool forward(int distance, int speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED);
    bool backward(int distance, int speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED)
    {
        return forward(-distance, speed);
    }
    bool handleMoveTo();
    void printHello();
    bool turn(int angle, int speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED);
    bool turnTo(int angle, int speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED);
    bool moveTo(Coord target, int speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED);
    bool reachedTarget();
    bool pause();
    bool resume();
    bool reset();
    void setCurrentCoords(int x, int y, float angle);
    void setCurrentCoords(Coord c);
    Coord getCurrentCoords();
    void checkPosition();
    void setSpeed(int speed);
    void setAcceleration(int acceleration);
    bool Run();
    bool diffMove(double angle, int ray, int speed=ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED);
    RobotMove();
};

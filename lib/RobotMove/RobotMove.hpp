#pragma once
#include <ROBOT_VARIABLES.h>
#include STEPPER_LIB

#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H
#endif

typedef struct {
    int x;
    int y;
    float angle;
}Coord;

typedef struct {
    int left;
    int right;
} ActionDistance;
class RobotMove
{
    protected:
    AccelStepper left, right;
    ActionDistance currentAction;
    public:
    Coord currentPos;
    bool forward(int distance, int speed=0);
    bool backward(int distance, int speed=0){
        return forward(-distance, speed);
    }
    bool turn(int angle, int speed=0);
    bool moveTo(Coord target, int speed=0);
    bool pause();
    bool resume();
    bool reset();
    RobotMove();
};


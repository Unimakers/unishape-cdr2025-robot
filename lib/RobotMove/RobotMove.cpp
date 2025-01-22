#include "RobotMove.hpp"
#ifndef ROBOT_VARIABLES_H
#include "ROBOT_VARIABLES.h"
#endif
/// @brief constructor for the RobotMove class
RobotMove::RobotMove():left(AccelStepper::DRIVER, PIN::STEPPERS::LEFT_STEP, PIN::STEPPERS::LEFT_DIR), right(AccelStepper::DRIVER, PIN::STEPPERS::RIGHT_STEP, PIN::STEPPERS::RIGHT_DIR)
{
    pinMode(PIN::STEPPERS::LEFT_ENABLE, OUTPUT);
    digitalWrite(PIN::STEPPERS::LEFT_ENABLE, LOW);
    pinMode(PIN::STEPPERS::RIGHT_ENABLE, OUTPUT);
    digitalWrite(PIN::STEPPERS::RIGHT_ENABLE, LOW);
    left.setPinsInverted(ROBOT_VARIABLES::STEPPER::LEFT_INVERTED);
    right.setPinsInverted(ROBOT_VARIABLES::STEPPER::RIGHT_INVERTED);
    currentPos = {0,0,0};
}
void RobotMove::printHello(){
    Serial.println("Hello");
}
/// @brief check if the robot has reached the target
/// @return true if the robot has reached the target else false
bool RobotMove::reachedTarget(){
    if(left.distanceToGo() == 0 && right.distanceToGo() == 0){
        return true;
    }
    return false;
}
/// @brief  go forward for a distance in mm with a speed in mm/s
/// @param distance 
/// @param speed 
/// @return return false if the robot is paused else true
bool RobotMove::forward(int distance, int speed){
    if(paused){
        return false;
    }
    Serial.println("Hello2Forward");
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    Serial.println("Okok");
    Serial.println("Speed : "+String(speed));
    Serial.println("Step Speed: "+String(ROBOT_VARIABLES::STEPPER::MmToStep(speed)));
    Serial.println("CurAction Left: "+String(currentAction.left));
    Serial.println("CurAction Right: "+String(currentAction.right));
    left.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    right.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    left.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    right.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    left.move(currentAction.left);
    right.move(currentAction.right);
    return true;
}

/// @brief move to a target coordinate with a speed in mm/s
/// @param target 
/// @param speed 
/// @return return false if the robot is paused else true
bool RobotMove::moveTo(Coord target, int speed){
    if(paused){
        return false;
    }
    int x = target.x - currentPos.x;
    int y = target.y - currentPos.y;
    int distance = sqrt(x*x + y*y);
    float angle = atan2(y,x);
    turnTo(angle);
    forward(distance, speed);
    return true;
}

/// @brief pause the robot
/// @return true
bool RobotMove::pause(){
    currentAction.left = left.distanceToGo();
    currentAction.right = right.distanceToGo();
    left.stop();
    right.stop();
    paused = true;
    return true;
}
/// @brief  resume the robot
/// @return true
bool RobotMove::resume(){
    Serial.println("Resume robot");
    left.move(currentAction.left);
    right.move(currentAction.right);
    paused = false;
    return true;
}
/// @brief reset tare the position of the robot
/// @return true
bool RobotMove::reset(){
    left.stop();
    right.stop();
    left.setCurrentPosition(0);
    right.setCurrentPosition(0);
    currentPos = {0,0,0};
    return true;
}
/// @brief set the current coordinates of the robot
/// @param x x coord
/// @param y y coord
/// @param angle angle of the robot in radians
void RobotMove::setCurrentCoords(int x,int y, float angle){
    setCurrentCoords(Coord{x,y,angle});
}
/// @brief set the current coordinates of the robot (using a Coord struct)
/// @param c Coord struct
void RobotMove::setCurrentCoords(Coord c){
    currentPos = c;
}
/// @brief get the current coordinates of the robot
/// @return Coord struct
Coord RobotMove::getCurrentCoords(){
    return currentPos;
}
bool RobotMove::Run(){
    left.run();
    right.run();
    return true;
}
/// @brief check the current position of the robot
void RobotMove::checkPosition(){
    currentPos.x = (left.currentPosition() + right.currentPosition())/2;
    currentPos.y = (left.currentPosition() + right.currentPosition())/2;
    currentPos.angle = (left.currentPosition() - right.currentPosition())/ROBOT_VARIABLES::STEPPER::STEPS_PER_MM;
}
/// @brief Turn the robot
/// @param angle angle in degrees
/// @param speed speed in mm/s
/// @return false if paused else true
bool RobotMove::turn(int angle, int speed){
    if(paused){
        return false;
    }
    int diameter = ROBOT_VARIABLES::WIDTH;
    double angleRad = ((double) angle) * PI / 180;
    Serial.println("AngleRad: "+String(angleRad));
    float circleArc = angleRad * (diameter/2);
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(circleArc);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(-circleArc);
    left.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    right.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    left.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    right.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    left.move(currentAction.left);
    right.move(currentAction.right);
    return true;
}
bool RobotMove::turnTo(int angle, int speed){
    if(paused){
        return false;
    }
    int angleToTurn = angle - currentPos.angle;
    turn(angleToTurn, speed);
    return true;
}
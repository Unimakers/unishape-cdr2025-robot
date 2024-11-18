#include "RobotMove.hpp"

RobotMove::RobotMove():left(AccelStepper::DRIVER, PIN::STEPPERS::LEFT_STEP, PIN::STEPPERS::LEFT_DIR), right(AccelStepper::DRIVER, PIN::STEPPERS::RIGHT_STEP, PIN::STEPPERS::RIGHT_DIR)
{
    pinMode(PIN::STEPPERS::ENABLE, OUTPUT);
    digitalWrite(PIN::STEPPERS::ENABLE, HIGH);
    left.setPinsInverted(ROBOT_VARIABLES::STEPPER::LEFT_INVERTED);
    right.setPinsInverted(ROBOT_VARIABLES::STEPPER::RIGHT_INVERTED);
    currentPos = {0,0,0};
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
bool RobotMove::forward(int distance, int speed=ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED){
    if(paused){
        return false;
    }
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    left.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    right.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    left.moveTo(left.currentPosition() + currentAction.left);
    right.moveTo(right.currentPosition() + currentAction.right);
    return true;
}
/// @brief move to a target coordinate with a speed in mm/s
/// @param target 
/// @param speed 
/// @return return false if the robot is paused else true
bool RobotMove::moveTo(Coord target, int speed=ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED){
    if(paused){
        return false;
    }
    int dx = target.x - currentPos.x;
    int dy = target.y - currentPos.y;
    float angle = atan2(dy,dx);
    int distance = sqrt(dx*dx + dy*dy);
    int angleToTurn = angle - currentPos.angle;
    turnTo(angleToTurn);
    forward(distance, speed);
    return true;
}
bool RobotMove::pause(){
    currentAction.left = left.distanceToGo();
    currentAction.right = right.distanceToGo();
    left.stop();
    right.stop();
    paused = true;
    return true;
}
bool RobotMove::resume(){
    left.moveTo(left.currentPosition() + currentAction.left);
    right.moveTo(right.currentPosition() + currentAction.right);
    paused = false;
    return true;
}
bool RobotMove::reset(){
    left.stop();
    right.stop();
    left.setCurrentPosition(0);
    right.setCurrentPosition(0);
    currentPos = {0,0,0};
    return true;
}
void RobotMove::setCurrentCoords(int x,int y, float angle){
    setCurrentCoords(Coord{x,y,angle});
}
void RobotMove::setCurrentCoords(Coord c){
    currentPos = c;
}
Coord RobotMove::getCurrentCoords(){
    return currentPos;
}
void RobotMove::checkPosition(){
    currentPos.x = (left.currentPosition() + right.currentPosition())/2;
    currentPos.y = (left.currentPosition() + right.currentPosition())/2;
    currentPos.angle = (left.currentPosition() - right.currentPosition())/ROBOT_VARIABLES::STEPPER::STEPS_PER_MM;
}

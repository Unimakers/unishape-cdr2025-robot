#include "RobotMove.hpp"
#ifndef ROBOT_VARIABLES_H
#include "ROBOT_VARIABLES.h"
#endif
/// @brief constructor for the RobotMove class
RobotMove::RobotMove():left(AccelStepper::DRIVER, PIN::STEPPERS::LEFT_STEP, PIN::STEPPERS::LEFT_DIR), right(AccelStepper::DRIVER, PIN::STEPPERS::RIGHT_STEP, PIN::STEPPERS::RIGHT_DIR)
{
    pinMode(PIN::STEPPERS::LEFT_ENABLE, OUTPUT);
    digitalWrite(PIN::STEPPERS::LEFT_ENABLE, LOW);
    left.setPinsInverted(ROBOT_VARIABLES::STEPPER::LEFT_INVERTED);
    right.setPinsInverted(ROBOT_VARIABLES::STEPPER::RIGHT_INVERTED);
    currentPos = {0,0,0};
}
void RobotMove::printHello(){
    debugPrintln("Hello");
}
/// @brief check if the robot has reached the target
/// @return true if the robot has reached the target else false
bool RobotMove::reachedTarget(){
    if(left.distanceToGo() == 0 && right.distanceToGo() == 0){
        switch (currentActionMoveTo.step)
        {
        case MoveToState::FIRST_TURN:
            currentActionMoveTo.step=MoveToState::MOVE;
            handleMoveTo();
            break;
        case MoveToState::MOVE:
            currentActionMoveTo.step=MoveToState::LAST_TURN;
            handleMoveTo();
            break;
        default:
            currentActionMoveTo.step=MoveToState::INACTIVE;
            break;
        }
        if(currentActionMoveTo.step!=MoveToState::INACTIVE){
            return false;
        }
        return true;
    }
    return false;
}

bool RobotMove::handleMoveTo(){
    if(paused){
        return false;
    }
    int x = currentActionMoveTo.target.x - currentPos.x;
    int y = currentActionMoveTo.target.y - currentPos.y;
    int distance = sqrt(x*x + y*y);
    float angle = atan2(y,x);
    if(currentActionMoveTo.step==MoveToState::MOVE){
        forward(distance, currentActionMoveTo.speed);
    }
    if(currentActionMoveTo.step==MoveToState::LAST_TURN){
        turnTo(currentActionMoveTo.target.angle);
    }
    return true;
}

/// @brief  go forward for a distance in mm with a speed in mm/s
/// @param distance 
/// @param speed 
/// @return return false if the robot is paused else true
bool RobotMove::forward(int distance, int speed){
    if(paused){
        return false;
    }
    // debugPrintln("Hello2Forward");
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(distance);
    // debugPrintln("Okok");
    // debugPrintln("Speed : "+String(speed));
    // debugPrintln("Step Speed: "+String(ROBOT_VARIABLES::STEPPER::MmToStep(speed)));
    // debugPrintln("CurAction Left: "+String(currentAction.left));
    // debugPrintln("CurAction Right: "+String(currentAction.right));
    left.setMaxSpeed(speed);
    right.setMaxSpeed(speed);
    left.setAcceleration(speed/2);
    right.setAcceleration(speed/2);
    Coord c = getCurrentCoords();
    setCurrentCoords(
        c.x+(cos(c.angle)*distance),
        c.y+(sin(c.angle)*distance),
        c.angle
    );
    // left.setMaxSpeed(200);
    // right.setMaxSpeed(200);
    // left.setAcceleration(100);
    // right.setAcceleration(100);
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
    currentActionMoveTo.step=MoveToState::FIRST_TURN;
    currentActionMoveTo.target=target;
    currentActionMoveTo.speed=speed;
    // forward(distance, speed);
    // turnTo(target.angle);
    return true;
}
void handleMoveTo(){
    
}
/// @brief pause the robot
/// @return true
bool RobotMove::pause(){
    currentAction.left = left.distanceToGo();
    currentAction.right = right.distanceToGo();
    left.move(0);
    right.move(0);
    currentAction.left = currentAction.left + left.distanceToGo();
    currentAction.right = currentAction.right + right.distanceToGo();
    paused = true;
    return true;
}
/// @brief  resume the robot
/// @return true
bool RobotMove::resume(){
    debugPrintln("Resume robot");
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

    // currentPos.x = (left.currentPosition() + right.currentPosition())/2;
    // currentPos.y = (left.currentPosition() + right.currentPosition())/2;
    // currentPos.angle = (left.currentPosition() - right.currentPosition())/ROBOT_VARIABLES::STEPPER::STEPS_PER_MM;
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
    double angleRad = ((double) angle) * PI / (double)180;
    debugPrintln("AngleRad: "+String(angleRad));
    float circleArc = angleRad * (diameter/2);
    debugPrintln("CircleArc: "+String(circleArc));
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(circleArc);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(-circleArc);
    left.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    right.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(speed));
    left.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    right.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    left.move(currentAction.left);
    right.move(currentAction.right);
    Coord c=getCurrentCoords();
    setCurrentCoords(c.x,c.y,c.angle+angleRad);
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
bool RobotMove::diffMove(double angle, int ray, int speed){
    if(paused){
        return false;
    }
    double angleRad = ((double) angle) * PI / (double)180;
    int diameter = ROBOT_VARIABLES::WIDTH;
    double left_c_width = ray-(diameter/2);
    double right_c_width = ray+(diameter/2);
    double left_length = angleRad*left_c_width;
    double right_length = angleRad*right_c_width;
    currentAction.left = ROBOT_VARIABLES::STEPPER::MmToStep(left_length);
    currentAction.right = ROBOT_VARIABLES::STEPPER::MmToStep(right_length);
    int lspeed,rspeed;
    if(left_length>right_length){
        lspeed=speed;
        rspeed=(lspeed/left_length)*right_length;
    }
    else{
        rspeed=speed;
        lspeed=(rspeed/right_length)*left_length;
    }
    debugPrint("LeftSpeed:");debugPrint(lspeed);debugPrint("RSpeed");debugPrintln(rspeed);
    left.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(lspeed));
    right.setMaxSpeed(ROBOT_VARIABLES::STEPPER::MmToStep(rspeed));
    left.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    right.setAcceleration(ROBOT_VARIABLES::STEPPER::MmToStep(ROBOT_VARIABLES::STEPPER::ACCELERATION));
    left.move(currentAction.left);
    right.move(currentAction.right);
    Coord currentCoord= getCurrentCoords();
    double absolute_yuri_angle = currentCoord.angle+(ray<0?-PI/2:PI/2);
    Coord yuri_rel= Coord{
        .x=cos(absolute_yuri_angle),
        .y=sin(absolute_yuri_angle)
    };
    Coord ray_center_coord=Coord{.x=currentCoord.x+yuri_rel.x,.y=currentCoord.y+yuri_rel.y};
    Coord pos_finale = Coord{
        .x=ray_center_coord.x+cos(currentCoord.angle+angleRad)*ray,
        .y=ray_center_coord.y+sin(currentCoord.angle+angleRad)*ray,
        .angle=currentCoord.angle+angleRad
    };
    setCurrentCoords(pos_finale);
    return true;
}
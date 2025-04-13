#include <ActionHandle.hpp>
#include <Arduino.h>
#include <ROBOT_VARIABLES.h>



ActionHandle::ActionHandle()
{
    this->robot = RobotMove();
    this->actionneur = Actionneur();
    this->Waitstart = 0;
    this->actionIndex = 0;
    this->state = STATE::INITIALIZING;

}


bool ActionHandle::actionfinished(ActionItem action)
{
    if (action.action == ACTION::WAIT)
    {
        if (millis() > this->Waitstart + action.time * 1000)
            return true;
        else
        {
            return false;
        }
    }
    else
    {
        return this->robot.reachedTarget();
    }
}
bool ActionHandle::callAction(ActionItem action)
{
    if (action.speed == 0)
        action.speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED;
    switch (action.action)
    {
    case ACTION::FORWARD:
        return this->robot.forward(action.distance, action.speed);
        break;
    case ACTION::BACKWARD:
        return this->robot.backward(action.distance, action.speed);
        break;
    case ACTION::TURN:
        return this->robot.turn(action.angle, action.speed);
        break;
    case ACTION::TURNTO:
        return this->robot.turnTo(action.angle, action.speed);
        break;
    case ACTION::MOVETO:
        return this->robot.moveTo(action.target, action.speed);
        break;
    case ACTION::PAUSE:
        return this->robot.pause();
        break;
    case ACTION::RESUME:
        return this->robot.resume();
        break;
    case ACTION::WAIT:
        return true;
        break;
    case ACTION::BUZZ:
        tone(12, action.tonality, action.time);
        return true;
        break;
    case ACTION::ACTIONNEUR_LIFT_UP:
        this->actionneur.monter();
        return true;
        break;
    case ACTION::ACTIONNEUR_LIFT_DOWN:
        this->actionneur.descendre();
        return true;
        break;
    case ACTION::ACTIONNEUR_GRAB:
        this->actionneur.pincer();
        return true;
        break;
    case ACTION::ACTIONNEUR_RELEASE:
        this->actionneur.relacher();
        return true;
        break;
    case ACTION::ACTIONNEUR_STOP:
        this->actionneur.stop();
        return true;
        break;
    default:
        return false;
    }
}
void ActionHandle::waitTirette()
{
    tone(12, 666, 250);
    while (digitalRead(PIN::DIVERS::TIRETTE))
    {
        Serial.println("Tirette absente");
        delay(500);
    }
    tone(12, 260, 250);
    Serial.println("Tirette en place");
    delay(1000);
    while (!digitalRead(PIN::DIVERS::TIRETTE))
        ;
    Serial.println("Tirette retirée");
    delay(1000);
    tone(12, 175, 250);
}
void ActionHandle::setState(STATE state){
    this->state = state;
}
void ActionHandle::actionLoop(){
    if (getState() == STATE::RUNNING)
    {
        if (actionfinished(getCurrentAction()) && getState() == STATE::RUNNING)
          {
            setState(STATE::IDLE);
        }
        else
        {
            this->robot.Run();
        }
    }
    if (getState() == STATE::IDLE)
    {
        if (this->actionIndex < DEV_VARIABLES::MAX_ACTION_AMOUNT)
        {
            setState(STATE::RUNNING);
            bool error = callAction(getCurrentAction());
            if (!error)
            {
                Serial.println("Erreur dans l'action");
            }
            this->actionIndex++;
        }
    }
}
ActionHandle::ActionItem ActionHandle::getAction(int index){
    if(index < 0 || index >= DEV_VARIABLES::MAX_ACTION_AMOUNT){
        Serial.println("Index out of range");
        return ActionItem{};
    }
    return this->actions[index];
}
ActionHandle::ActionItem ActionHandle::getCurrentAction(){
    return this->actions[this->actionIndex];
}
void ActionHandle::addAction(ActionItem action){
    this->actions.push_back(action);
}
void ActionHandle::addActionEasy(ACTION action,ActionItem actionvar){
    ActionItem newAction;
    newAction.action = action;
    newAction.distance = actionvar.distance;
    newAction.speed = actionvar.speed;
    newAction.angle = actionvar.angle;
    newAction.time = actionvar.time;
    newAction.target = actionvar.target;
    this->actions.push_back(newAction);
}
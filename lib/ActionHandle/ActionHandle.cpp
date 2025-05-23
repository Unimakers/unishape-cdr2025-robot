#include <ActionHandle.hpp>


ActionHandle::ActionHandle()
{
    // this->actionneur = Actionneur();
    this->Waitstart = 0;
    this->actionIndex = 0;
    this->state = STATE::INITIALIZING;

}
ActionHandle::STATE ActionHandle::getState(){
    return this->state;
}
void ActionHandle::initRobot(){
    this->robot = RobotMove();
    this->robot.resume();
    this->robot.printHello();
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
    case ACTION::DIFFMOVE:
        debugPrintln("diffmove!!!");
        return this->robot.diffMove(action.angle,action.distance,action.speed);
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
        superbuzz(action.tonality, action.time);
        return true;
        break;
    // case ACTION::ACTIONNEUR_LIFT_UP:
    //     this->actionneur.monter();
    //     return true;
    //     break;
    // case ACTION::ACTIONNEUR_LIFT_DOWN:
    //     this->actionneur.descendre();
    //     return true;
    //     break;
    // case ACTION::ACTIONNEUR_GRAB:
    //     this->actionneur.pincer();
    //     return true;
    //     break;
    // case ACTION::ACTIONNEUR_RELEASE:
    //     this->actionneur.relacher();
    //     return true;
    //     break;
    // case ACTION::ACTIONNEUR_STOP:
    //     this->actionneur.stop();
    //     return true;
    //     break;
    default:
        return false;
    }
}
void ActionHandle::waitTirette()
{
    superbuzz(666, 250);
    while (digitalRead(PIN::DIVERS::TIRETTE))
    {
        debugPrintln("Tirette absente");
        delay(500);
    }
    superbuzz(260, 250);
    debugPrintln("Tirette en place");
    delay(1000);
    while (!digitalRead(PIN::DIVERS::TIRETTE))
        ;
    debugPrintln("Tirette retirée");
    delay(1000);
    superbuzz(175, 250);
}
void ActionHandle::setState(STATE state){
    this->state = state;
}
void ActionHandle::actionLoop(){
    // debugPrintln("entering first step of debug");
    // debugPrintln(((std::string)"Actions is of size: "+std::to_string(actions.size())).c_str());
    if (getState() == STATE::RUNNING)
    {
        // debugPrintln("entering sec1 step of debug");
        if (actionfinished(getRunningAction()) && getState() == STATE::RUNNING)
        {
            // debugPrintln("action fini");
            setState(STATE::IDLE);
        }
        else
        {
            // debugPrintln(((std::string)"run!!!"+std::to_string(millis())).c_str());
            this->robot.Run();
        }
    }
    else if (getState() == STATE::IDLE)
    {
        // debugPrintln("entering sec2 step of debug");
        // debugPrintln("hellow");
        // debugPrintln(DEV_VARIABLES::MAX_ACTION_AMOUNT);
        if (this->actionIndex < actions.size())
        {
            debugPrintln("helloworld1");
            setState(STATE::RUNNING);
            // debugPrintln(getCurrentAction().distance);
            bool error = callAction(getCurrentAction());
            if (!error)
            {
                debugPrintln("Erreur dans l'action");
            }
            this->actionIndex++;
        }
    }else if (getState()==STATE::PAUSED){
        robot.Run();
    }
}
ActionHandle::ActionItem ActionHandle::getAction(int index){
    // debugPrintln("inside get Sec");
    if(index < 0 || index >= actions.size()){
        debugPrintln("Index out of range");
        return ActionItem{};
    }
    return this->actions[index];
}
ActionHandle::ActionItem ActionHandle::getCurrentAction(){
    // debugPrintln("inside getCurr");
    return getAction(this->actionIndex);
}
ActionHandle::ActionItem ActionHandle::getRunningAction(){
    return getAction(this->actionIndex-1);
}
void ActionHandle::addAction(ActionItem action){
    debugPrintln("wow i receive an action!");
    debugPrintln(debugActionString(action).c_str());
    this->actions.push_back(action);
    debugPrintln(this->actions.size());
}
void ActionHandle::addActionEasy(ACTION action,ActionItem actionvar){
    ActionItem newAction;
    newAction.action = action;
    newAction.distance = actionvar.distance;
    newAction.speed = actionvar.speed;
    newAction.angle = actionvar.angle;
    newAction.time = actionvar.time;
    newAction.target = actionvar.target;
    addAction(newAction);
}
void ActionHandle::setRobotCoord(Coord coord){
    this->robot.setCurrentCoords(coord);
}
void ActionHandle::pauseLidar(){
    if(this->getState()!=STATE::PAUSED){
        this->setState(STATE::PAUSED);
        robot.pause();
    }
}
void ActionHandle::continueLidar(){
    if(this->getState()==STATE::PAUSED){
        this->setState(STATE::RUNNING);
        robot.resume();
    }
}
std::string ActionHandle::debugActionString(ActionItem actItem){
    std::string actionStr = debugActionEnumString(actItem.action);
    return 
    "ActionItem{\n"
    "\taction:"+actionStr+"\n"
    "\tdistance:"+std::to_string(actItem.distance)+"\n"
    "\tspeed:"+std::to_string(actItem.speed)+"\n"
    "\tangle:"+std::to_string(actItem.angle)+"\n"
    "\ttime:"+std::to_string(actItem.time)+"\n"
    "\ttonality:"+std::to_string(actItem.tonality)+"\n"
    "\ttarget:"+debugCoordString(actItem.target)+"\n"
    "}";
}
std::string ActionHandle::debugCoordString(Coord c){
    return "Coord{x="+std::to_string(c.x)+"y="+std::to_string(c.y)+"a="+std::to_string(c.angle)+"}";
}
std::string ActionHandle::debugActionEnumString(ACTION act){
    switch (act)
    {
    case ACTION::FORWARD:
        return "FORWARD";
        break;
    case ACTION::BACKWARD:
        return "BACKWARD";
        break;
    case ACTION::TURN:
        return "TURN";
        break;
    case ACTION::TURNTO:
        return "TURNTO";
        break;
    case ACTION::MOVETO:
        return "MOVETO";
        break;
    case ACTION::PAUSE:
        return "PAUSE";
        break;
    case ACTION::RESUME:
        return "RESUME";
        break;
    case ACTION::WAIT:
        return "WAIT";
        break;  
    case ACTION::BUZZ:
        return "BUZZ";
        break;
    case ACTION::ACTIONNEUR_LIFT_UP:
        return "ACTIONNEUR_LIFT_UP";
        break;
    case ACTION::ACTIONNEUR_LIFT_DOWN:
        return "ACTIONNEUR_LIFT_DOWN";
        break;
    case ACTION::ACTIONNEUR_GRAB:
        return "ACTIONNEUR_GRAB";
        break;
    case ACTION::ACTIONNEUR_RELEASE:
        return "ACTIONNEUR_RELEASE";
        break;
    case ACTION::ACTIONNEUR_STOP:
        return "ACTIONNEUR_STOP";
        break;
    case ACTION::DIFFMOVE:
        return "DIFFMOVE";
        break;
    default:
        break;
    }
    return "UNKNOWN";
}
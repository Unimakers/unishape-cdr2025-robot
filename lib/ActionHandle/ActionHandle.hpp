#include <RobotMove.hpp>
#include <actionneur.hpp>
#include <vector>
class ActionHandle
{
protected:
    RobotMove robot;
    Actionneur actionneur;
    float Waitstart = 0;
    int actionIndex = 0;

public:
    enum struct ACTION
    {
        FORWARD,
        BACKWARD,
        TURN,   // tourne retation relative
        TURNTO, // tourne jusqu'a votre un angle donnée
        MOVETO,
        PAUSE, // arret des mouvement
        RESUME,
        WAIT, // attendre  un certains temps des ordre du h
        BUZZ,
        ACTIONNEUR_LIFT_UP,
        ACTIONNEUR_LIFT_DOWN,
        ACTIONNEUR_GRAB,
        ACTIONNEUR_RELEASE,
        ACTIONNEUR_STOP
    };
    typedef struct
    {
        ACTION action;
        int distance, speed, angle, time, tonality;
        Coord target;
    } ActionItem;
    typedef std::vector<ActionItem> Actions;
    enum struct STATE
    {
        INITIALIZING,
        IDLE,
        RUNNING,
        PAUSED // paused by security and not by external event => pause non programmed in action list (e.g. lidar detects obstacle)
    };
    STATE state = STATE::INITIALIZING;
    Actions actions;
    ActionHandle();
    void waitTirette();
    bool actionfinished(ActionItem action);
    bool callAction(ActionItem action);
    void setState(STATE state);
    STATE getState();
    void actionLoop();
    ActionItem getAction(int index);
    ActionItem getCurrentAction();
    void addAction(ActionItem action);
    void addActionEasy(ACTION action,ActionItem actionvar={});
    void initRobot();
};
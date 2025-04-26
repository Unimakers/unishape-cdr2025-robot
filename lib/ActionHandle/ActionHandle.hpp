#pragma once
#ifndef ACTION_HANDLE_H
#define ACTION_HANDLE_H
#endif
#include "RobotMove.hpp"
// #include "actionneur.hpp"
#include <vector>
#include <Arduino.h>
#include "ROBOT_VARIABLES.h"
#include <string>
class ActionHandle
{
protected:
    RobotMove robot;
    // Actionneur actionneur;
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
    void setRobotCoord(Coord c);
    static std::string debugActionString(ActionItem actItem);
    static std::string debugActionEnumString(ACTION act);
    static std::string debugCoordString(Coord c);
    static void superbuzz(unsigned int frequency, unsigned long duration =0L){
        Serial.println(((std::string)"music! "+std::to_string(frequency)+" &"+std::to_string(duration)+"s").c_str());
    }
    
};

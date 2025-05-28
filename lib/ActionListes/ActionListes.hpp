#pragma once
#ifndef ACTION_LISTE_H
#define ACTION_LISTE_H
#endif
#include "ActionHandle.hpp"
#define ACT ActionHandle::ACTION
class ActionList
{
    protected:
    ActionHandle::Actions actions;
    typedef struct {
        int distance, speed, angle, time, tonality;
        Coord target;
    } ActVar;
    bool teamBlue = true;
    public:
    ActionList(){};
    void NAction(ACT action, ActVar actionvar){
        if(ActionHandle::debugActionEnumString(action)=="UNKNOWN") return;
        ActionHandle::ActionItem actionItem = ActionHandle::ActionItem{};
        debugPrintln("from here");
        actionItem.action = action;
        actionItem.distance = actionvar.distance;
        actionItem.speed = actionvar.speed;
        actionItem.angle = actionvar.angle;
        actionItem.time = actionvar.time;
        actionItem.target = actionvar.target;
        debugPrintln(ActionHandle::debugActionString(actionItem).c_str());
        actions.push_back(actionItem);
    }
    void pushAction(ActionHandle* actionHandle){
        this->teamBlue=false;//(bool)digitalRead(PIN::DIVERS::TEAM_SWITCH);
        debugPrintln("wow!");
        initialCoord(actionHandle);
        strat();
        for (auto action : actions)
        {
            (*actionHandle).addAction(action);
        }
    }
    void initialCoord(ActionHandle* actionHandle);
    void strat();
};
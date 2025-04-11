#include <ActionHandle.hpp>
#define ACT ActionHandle::ACTION
class ActionList
{
    protected:
    ActionHandle::Actions actions;
    public:
    void NAction(ACT action, ActionHandle::ActionItem actionvar){
        ActionHandle::ActionItem actionItem;
        actionItem.action = action;
        actionItem.distance = actionvar.distance;
        actionItem.speed = actionvar.speed;
        actionItem.angle = actionvar.angle;
        actionItem.time = actionvar.time;
        actionItem.target = actionvar.target;
        actions.push_back(actionItem);
    }
    void pushAction(ActionHandle actionHandle){
        strat();
        for (auto action : actions)
        {
            actionHandle.addAction(action);
        }
    }
    void strat();
};

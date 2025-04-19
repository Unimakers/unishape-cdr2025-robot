#include <ActionListes.hpp>

void ActionList::initialCoord(ActionHandle actionHandle){
    if(this->teamBlue) actionHandle.setRobotCoord({2650, 1800, 0});
    else actionHandle.setRobotCoord({350, 1800, 0});
}
void ActionList::strat(){
    if(this->teamBlue){
        NAction(ACT::MOVETO, ActVar{.target = Coord{2225,450,0}});
        NAction(ACT::FORWARD, ActVar{.distance = 300});
        NAction(ACT::BACKWARD, ActVar{.distance = 300});
        NAction(ACT::MOVETO, ActVar{.target = Coord{2650,1800,0}});
    }else{
        NAction(ACT::MOVETO, ActVar{.target = Coord{775,450,0}});
        NAction(ACT::FORWARD, ActVar{.distance=300});
        NAction(ACT::BACKWARD, ActVar{.distance=300});
        NAction(ACT::MOVETO, ActVar{.target=Coord{350,1800,0}});
    }
}
#include <ActionListes.hpp>

void ActionList::initialCoord(ActionHandle* actionHandle){
    if(this->teamBlue) (*actionHandle).setRobotCoord({2650, 1800, 0});
    else (*actionHandle).setRobotCoord({350, 1800, 0});
}
void ActionList::strat(){
    // NAction(ACT::FORWARD, ActVar{.distance=10000});
    // NAction(ACT::DIFFMOVE,ActVar{.distance=100,.speed=2000,.angle=90});
    // NAction(ACT::DIFFMOVE,ActVar{.distance=200,.speed=2000,.angle=-100});
    // NAction(ACT::DIFFMOVE,ActVar{.distance=0,.speed=2000,.angle=280});
    NAction(ACT::FORWARD, ActVar{.distance=1000,.speed=5000});
    NAction(ACT::BACKWARD, ActVar{.distance=1000,.speed=5000});
    NAction(ACT::FORWARD, ActVar{.distance=1000,.speed=5000});
    NAction(ACT::BACKWARD, ActVar{.distance=1000,.speed=5000});
    // if(this->teamBlue){
    //     NAction(ACT::MOVETO, ActVar{.target = Coord{2225,450,0}});
    //     NAction(ACT::FORWARD, ActVar{.distance = 300});
    //     NAction(ACT::BACKWARD, ActVar{.distance = 300});
    //     NAction(ACT::MOVETO, ActVar{.target = Coord{2650,1800,0}});
    //     NAction(ACT::TURN, ActVar{.angle=90});
    // }else{
    //     NAction(ACT::MOVETO, ActVar{.target = Coord{775,450,0}});
    //     NAction(ACT::FORWARD, ActVar{.distance=300});
    //     NAction(ACT::BACKWARD, ActVar{.distance=300});
    //     NAction(ACT::MOVETO, ActVar{.target=Coord{350,1800,0}});
    //     NAction(ACT::TURN, ActVar{.angle=90});
    // }
}
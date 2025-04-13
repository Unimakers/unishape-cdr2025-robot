#include <Arduino.h>
#include <RobotMove.hpp>
#include <lidar.c++>
#include <actionneur.hpp>
#include <ActionHandle.hpp>

RobotMove robot;
Actionneur actionneur;
ActionHandle actionHandle;



// put function declarations here:

// int startTime=0;
void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Préinitialisation");
    robot = RobotMove();
    actionneur = Actionneur();
    actionHandle = ActionHandle(robot,actionneur);
    tone(12, 444, 250);
    initLidar();
    // lidarSerial.begin(115200, 134217756U, RX, TX);

    delay(500);
    pinMode(PIN::DIVERS::TIRETTE, INPUT_PULLUP);
    tone(12, 300, 250);
    actionHandle.waitTirette();
    robot.resume();
    robot.printHello();
    Serial.println("Fin initialisation");
    actionHandle.setState(ActionHandle::STATE::IDLE);
    robot.setCurrentCoords(Coord{0, 0, 0});
    // startTime= millis();
}
void loop()
{
    if (getLidarStatus())
    {
        actionHandle.setState(ActionHandle::STATE::PAUSED);
    }
    actionHandle.actionLoop();
}
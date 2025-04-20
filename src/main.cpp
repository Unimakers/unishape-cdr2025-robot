#include <Arduino.h>

#define BONJOUR 1
#if BONJOUR == 0
// DEBUG
// ça marche pas...
#include <RobotMove.hpp>
RobotMove rob;
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-S3 Startup");
  rob = RobotMove();
  rob.forward(1000,20);
}
//DOOOOOODOOOOOOOOOOOOOOOOOOOOO jvais dormir par terre sinon.....
void loop() {
  Serial.println("Loop running");
  rob.Run();
  
  delay(1000);
}
// FIN DEBUG
#else



#include <lidar.c++>
#include <ActionHandle.hpp>
#include <ActionListes.hpp>
#include <string>

ActionHandle actionHandle;

enum struct G_STATE
{
    INITIALIZING,
    LOOPING
};
G_STATE gState=G_STATE::INITIALIZING;

// put function declarations here:
//
// int startTime=0;
void setup()
{
    gState=G_STATE::INITIALIZING;
    Serial.begin(115200);
    delay(1000);
    Serial.println("Préinitialisation");
    actionHandle = ActionHandle();
    ActionList actionList = ActionList();
    actionList.pushAction(&actionHandle);
    Serial.println(((std::string)"final op : "+std::to_string(actionHandle.actions.size())).c_str());
    tone(12, 444, 250);
    initLidar();
    // lidarSerial.begin(115200, 134217756U, RX, TX);
    //
    delay(500);
    pinMode(PIN::DIVERS::TIRETTE, INPUT_PULLUP);
    tone(12, 300, 250);
    actionHandle.waitTirette();
    actionHandle.initRobot();
    Serial.println("Fin initialisation");
    actionHandle.setState(ActionHandle::STATE::IDLE);
    gState=G_STATE::LOOPING;
    Serial.println("Vraiment fin init");
    // startTime= millis();
}
void loop(){

    Serial.println("err1");
    if(gState!=G_STATE::LOOPING) return;
    Serial.println("err2");
    if (getLidarStatus())
    {
        actionHandle.setState(ActionHandle::STATE::PAUSED);
    }
    Serial.println("err3");
    actionHandle.actionLoop();
    delay(250);
}
#endif
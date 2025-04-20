#include <Arduino.h>

#define BONJOUR 2
#if BONJOUR == 2
#include <Arduino.h>
#include <RPLidar.h>
#include <string>
#include <SPI.h>
#include <Wire.h>
#include <ROBOT_VARIABLES.h>
RPLidar lidar;
HardwareSerial lidarSerial(0);
TaskHandle_t Task0;
void LidarProcess(void *);
void setup()
{
    Serial.begin(115200);
    Serial.println("setup");
    pinMode(PIN::LIDAR::PWM, OUTPUT);
    analogWrite(PIN::LIDAR::PWM, 150);
    xTaskCreatePinnedToCore(LidarProcess, "Task0", 1000, NULL, 1, &Task0, 0);
}

typedef struct RPLidarMeasurement RPLIDARRES;
void loop()
{
    Serial.println("hello from core 1");
}

void LidarProcess(void *pvParameters)
{
    lidar.begin(Serial0);
    lidar.startScan();
    for (;;)
    {
        Serial.print("loop core0 :");
        Serial.println(millis());
        // toujours au meme endroit, le IS_OK(lidar.waitPoint()) crée un stack canary watchpoint trigger sur le core 0
        if (IS_OK(lidar.waitPoint()))
        {
            RPLIDARRES mesureRes = lidar.getCurrentPoint();
            if (mesureRes.distance < 1000 && mesureRes.quality > 14)
            {
                float angle = mesureRes.angle * (float)DEG_TO_RAD;
                float distance = mesureRes.distance;
                float x = cos(angle) * distance;
                float y = sin(angle) * distance;
                Serial.print(">point:");
                Serial.print((double)x);
                Serial.print(":");
                Serial.print((double)y);
                // Serial.print(":");
                // Serial.print((double)millis());
                Serial.println("|xy");
                delay(250);
            }
        }
        else
        {
            // analogWrite(D0, 0); // stop the rplidar motor
            Serial.println("Lidar Stopped");
            // try to detect RPLIDAR...
            rplidar_response_device_info_t info;
            if (IS_OK(lidar.getDeviceInfo(info, 100)))
            {
                Serial.println("Lidar found");
                // detected...
                lidar.startScan();
                // analogWrite(D0, 150);
                delay(1000);
            }
            else
            {
                Serial.println("Lidar not found");
            }
        }
        delay(25);
    }
}


#elif BONJOUR == 0
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
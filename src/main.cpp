#include <Arduino.h>
#include <RobotMove.hpp>

enum struct STATE{
    IDLE,
    MOVING,
    PAUSED
};
// put function declarations here:
void waitTirette(){
    tone(12,666,250);
    while(digitalRead(PIN::DIVERS::TIRETTE)){
    Serial.println("Tirette absente");
    delay(500);
    }
    tone(12,260,250);
    Serial.println("Tirette en place");
    delay(1000);
    while(!digitalRead(PIN::DIVERS::TIRETTE));
    Serial.println("Tirette retirée");
    delay(1000);
    tone(12,175,250);
}
RobotMove robot = RobotMove();
// int startTime=0;
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Préinitialisation");
    tone(12,444,250);
    robot.forward(100);
    delay(500);
    pinMode(PIN::DIVERS::TIRETTE,INPUT_PULLUP);
    tone(12,300,250);
    waitTirette();
    Serial.println("Initialisation");
    // startTime= millis();
}
void loop() {
    robot.Run();
    // if(millis()-startTime>=20000){
    //     robot.pause();
    //     for(;;);
    // }
}

// put function definitions here:
int myFunction(int x, int y) {
    return x + y;
}
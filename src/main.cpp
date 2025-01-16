#include <Arduino.h>
#include <RobotMove.hpp>


enum struct STATE{
    IDLE,
    MOVING,
    PAUSED
};
// put function declarations here:
void waitTirette(){
    while(digitalRead(PIN::DIVERS::TIRETTE));
    Serial.println("Tirette enclenchée");
    delay(1000);
    while(!digitalRead(PIN::DIVERS::TIRETTE));
    Serial.println("Tirette retirée");
    delay(1000);
}
void setup() {
    Serial.begin(115200);
    delay(250);
    Serial.println("Préinitialisation");
    waitTirette();
    Serial.println("Initialisation");
}

void loop() {
    // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
    return x + y;
}
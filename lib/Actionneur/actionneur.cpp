#include <actionneur.hpp>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*
----------ACTIONNEUR----------
servoLL , servoLR, servoRL, servoRR
           servoLift
------------------------------
*/

Actionneur::Actionneur()
{
    // pca.writeMicroseconds(servoLL, 1500);
    pca = Adafruit_PWMServoDriver(0x40);
    servoLL = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_LL;
    servoLR = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_LR;
    servoRL = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_RL;
    servoRR = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_RR;
    servoLift = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_LIFT;
}

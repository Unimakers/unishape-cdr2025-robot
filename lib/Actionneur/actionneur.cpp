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
    servoL = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_L;
    servoL = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_R;
    servoLiftL = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_LIFT_L;
    servoLiftR = PIN::ACTIONNEUR::SERVO_PCA9685::SERVO_LIFT_R;
    pca.begin();
    pca.setPWMFreq(60);
}

void Actionneur::monter(){
    pca.writeMicroseconds(servoLiftL, deg2ms(90));
    pca.writeMicroseconds(servoLiftR, deg2ms(90));
}


void Actionneur::pincer()
{
    pca.writeMicroseconds(servoL,deg2ms(90));
    pca.writeMicroseconds(servoR,deg2ms(90));
}
unsigned int deg2ms(unsigned int degree)
{
    return map(degree, 0,180,1000,2000);
}

void Actionneur::relacher()
{
    pca.writeMicroseconds(servoL,deg2ms(0));
    pca.writeMicroseconds(servoR,deg2ms(0));
}

void Actionneur::descendre(){
    pca.writeMicroseconds(servoLiftL, deg2ms(0));
    pca.writeMicroseconds(servoLiftR, deg2ms(0));
}
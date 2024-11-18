#pragma once
#ifndef TEST_STEPPER_H
#define TEST_STEPPER_H
#endif
#include <iostream>

class AccelStepper
{
    typedef enum
    {
	FUNCTION  = 0,
	DRIVER    = 1,
	FULL2WIRE = 2,
	FULL3WIRE = 3,
        FULL4WIRE = 4,
	HALF3WIRE = 6,
	HALF4WIRE = 8 
    } MotorInterfaceType;
    AccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
    void moveTo(long absolute); 
    void move(long relative);
    bool run();
    bool runSpeed();
    void setMaxSpeed(float speed);
    float maxSpeed();
    void setAcceleration(float acceleration);
    void setSpeed(float speed);
    float speed();
    long distanceToGo();
    long targetPosition();
    long currentPosition();
    void setCurrentPosition(long position);
    void runToPosition();
    bool runSpeedToPosition();
    void runToNewPosition(long position);
    void stop();
    virtual void disableOutputs();
    virtual void enableOutputs();
    void setMinPulseWidth(unsigned int minWidth);
    void setEnablePin(uint8_t enablePin = 0xff);
    void setPinsInverted(bool directionInvert = false, bool stepInvert = false, bool enableInvert = false);
    void setPinsInverted(bool pin1Invert, bool pin2Invert, bool pin3Invert, bool pin4Invert, bool enableInvert);



};

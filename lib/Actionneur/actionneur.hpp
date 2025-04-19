#pragma once
#include "ROBOT_VARIABLES.h"
#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#ifndef ACTIONNEUR_H
#define ACTIONNEUR_H
#endif


class Actionneur
{
    protected:
        int servoL,servoR, servoLiftL, servoLiftR;
        Adafruit_PWMServoDriver pca;
    public:
        Actionneur();
        void monter();
        void descendre();
        void stop();
        void pincer();
        void relacher();
};
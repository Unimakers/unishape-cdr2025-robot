#pragma once
#include "ROBOT_VARIABLES.h"
#include <AccelStepper.h>

#ifndef ACTIONNEUR_H
#define ACTIONNEUR_H
#endif


class Actionneur
{
    protected:
        AccelStepper ascenseur;
        int stepMotorLL,stepMotorLR,stepMotorRL,stepMotorRR;
    public:
        Actionneur();
        void monter();
        void descendre();
        void stop();
        void pincer();
        void relacher();
};
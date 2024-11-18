#pragma once

#ifndef ROBOT_VARIABLES_H
#define ROBOT_VARIABLES_H
#endif 

#define TEAM_NAME "UniGaffer"

namespace PIN
{
    namespace STEPPERS
    {
        constexpr int 
                    LEFT_STEP = 2,
                    RIGHT_STEP = 3,
                    LEFT_DIR = 4,
                    RIGHT_DIR = 5;
    }
} // namespace PIN

#define WHEEL_DIAMETER 0.06 // 0.06 m = 6cm
#define STEPPER_ANGLE 1.8 // 1.8 degrees per step
#define STEPPER_STEPS_PER_REV 200 // 200 steps per revolution


#if !TEST_MODE
#define STEPPER_LIB <AccelStepper.h>
#else

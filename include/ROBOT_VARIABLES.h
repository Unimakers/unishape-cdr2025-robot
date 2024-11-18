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
                    RIGHT_DIR = 5,
                    ENABLE=6;
    }
} // namespace PIN
namespace ROBOT_VARIABLES{
    constexpr float WHEEL_DIAMETER = 0.06; // 0.06 m = 6cm
    namespace STEPPER{
        constexpr float MmToStep(float mm){
            return mm * STEPS_PER_MM;
        }
        constexpr float StepToMm(float step){
            return step / STEPS_PER_MM;
        }
        constexpr float 
            ANGLE = 1.8, // 1.8 degrees per step
            STEPS_PER_REV = 200.0, // 200 steps per revolution
            STEPS_PER_MM = STEPS_PER_REV / (WHEEL_DIAMETER * 3.14159265359),// 200 steps per revolution / (0.06m * 3.14159265359)
            DEFAULT_SPEED = 50.0; // 50 mm/s
        constexpr bool LEFT_INVERTED = false,
                        RIGHT_INVERTED = false;

    }

}


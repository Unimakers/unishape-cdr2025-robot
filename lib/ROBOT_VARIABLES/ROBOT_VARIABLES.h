#pragma once

#ifndef ROBOT_VARIABLES_H
#define ROBOT_VARIABLES_H
#endif

#define TEAM_NAME "UniGaffer"
// 0 = UNISHAPE, 1= PAMITEST, 2= UNIWIP
#define TEST_ROBOT_MODE 0


#define debugPrint Serial.print
#define debugPrintln Serial.println
#define infoPrintln Serial.println
#define infoPrint Serial.print

namespace PIN
{
    namespace STEPPERS
    {
        constexpr int
// #if TEST_ROBOT_MODE == 1
//             LEFT_STEP = 6,
//             LEFT_DIR = 7,
//             RIGHT_STEP = 38,
//             RIGHT_DIR = 36,
//             LEFT_ENABLE = 8,
//             RIGHT_ENABLE = 1;
// #elif TEST_ROBOT_MODE == 2
//             LEFT_STEP = 14,
//             RIGHT_STEP = 12,
//             LEFT_DIR = 13,
//             RIGHT_DIR = 11,
//             LEFT_ENABLE = 46,
//             RIGHT_ENABLE = 46;
// #else
            LEFT_STEP = 14,
            RIGHT_STEP = 12,
            LEFT_DIR = 13,
            RIGHT_DIR = 11,
            LEFT_ENABLE = 46,
            RIGHT_ENABLE = 46;
// #endif
    }
    namespace LIDAR
    {
        constexpr int PWM = 3;
    }
    namespace ACTIONNEUR
    {
        namespace SERVO_PCA9685
        {
            constexpr int SERVO_L = 0,
                          SERVO_R = 1,
                          SERVO_LIFT_L = 2,
                          SERVO_LIFT_R = 3;
        }
    }
    namespace DIVERS
    {
        constexpr int
// #if TEST_ROBOT_MODE == 1
//             TIRETTE = 3;
// #elif TEST_ROBOT_MODE == 2
//             TIRETTE = 8;
// #else
            TIRETTE = 8,
            TEAM_SWITCH = 1;
// #endif
    }
} // namespace PIN
namespace DEV_VARIABLES
{
    constexpr int
        DEV_TEST_IN_ROBOT = TEST_ROBOT_MODE,
        MAX_ACTION_AMOUNT = 20;
}
namespace ROBOT_VARIABLES
{
    constexpr float WHEEL_DIAMETER = 60; // 60 mm = 6cm
    constexpr int MICROSTEP_FACTOR = 16; // 1/16 microstep
    constexpr float WIDTH = 300; // 300 mm = 30 cm
    namespace STEPPER // Stepper vars
    {
        constexpr int
            DEFAULT_SPEED = 200; // 200 mm/s
        constexpr float
            ANGLE = 1.8,           // 1.8 degrees per step
            ACCELERATION = 5000.0,  // 100 mm/s^2
            STEPS_PER_REV = 200.0*MICROSTEP_FACTOR; // 200 steps per revolution
        constexpr bool
            LEFT_INVERTED = false, // is left inverted ?
            RIGHT_INVERTED = true; // is right inverted ?
        constexpr float STEPS_PER_MM = STEPS_PER_REV / (WHEEL_DIAMETER * 3.14159265359); // 200 steps per revolution / (0.06m * 3.14159265359)
        /// @brief super mm to step convert
        /// @param mm mm to convert
        /// @return step from mm
        constexpr float MmToStep(float mm)
        {
            return mm * STEPS_PER_MM;
        }
        constexpr float StepToMm(float step)
        {
            return step / STEPS_PER_MM;
        }
        constexpr float SSS= MmToStep(20);

    }

};
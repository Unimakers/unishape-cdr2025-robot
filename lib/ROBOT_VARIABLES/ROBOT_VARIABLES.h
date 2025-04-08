#pragma once

#ifndef ROBOT_VARIABLES_H
#define ROBOT_VARIABLES_H
#endif

#define TEAM_NAME "UniGaffer"
// 0 = UNISHAPE, 1= PAMITEST, 2= UNIWIP
#define TEST_ROBOT_MODE 0

namespace PIN
{
    namespace STEPPERS
    {
        constexpr int
#if TEST_ROBOT_MODE == 1
            LEFT_STEP = 6,
            LEFT_DIR = 7,
            RIGHT_STEP = 38,
            RIGHT_DIR = 36,
            LEFT_ENABLE = 8,
            RIGHT_ENABLE = 1;
#elif TEST_ROBOT_MODE == 2
            LEFT_STEP = 14,
            RIGHT_STEP = 12,
            LEFT_DIR = 13,
            RIGHT_DIR = 11,
            LEFT_ENABLE = 46,
            RIGHT_ENABLE = 46;
#else
            LEFT_STEP = 2,
            RIGHT_STEP = 3,
            LEFT_DIR = 4,
            RIGHT_DIR = 5,
            LEFT_ENABLE = 6,
            RIGHT_ENABLE = 7;
#endif
    }
    namespace LIDAR{
    }
    namespace DIVERS
    {
        constexpr int
#if TEST_ROBOT_MODE == 1
            TIRETTE = 3;
#elif TEST_ROBOT_MODE == 2
            TIRETTE = 8;
#else
            TIRETTE = 8;
#endif
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
#if TEST_ROBOT_MODE == 1
    constexpr float WHEEL_DIAMETER = 0.07; // 0.07 m = 7cm
#elif TEST_ROBOT_MODE == 2
    constexpr float WHEEL_DIAMETER = 0.06; // 0.06 m = 6cm
#else
    constexpr float WHEEL_DIAMETER = 0.06; // 0.06 m = 6cm
#endif
#if TEST_ROBOT_MODE == 1
    constexpr float WIDTH = 95; // 95 mm = 9.5 cm
#elif TEST_ROBOT_MODE == 2
    constexpr float WIDTH = 245; // 300 mm = 30 cm
#else
    constexpr float WIDTH = 300; // 300 mm = 30 cm
#endif
    namespace STEPPER
    {
        constexpr int
            DEFAULT_SPEED = 200; // 200 mm/s
        constexpr float
            ANGLE = 1.8,           // 1.8 degrees per step
            ACCELERATION = 100.0,  // 100 mm/s^2
            STEPS_PER_REV = 200.0; // 200 steps per revolution
        constexpr bool
            LEFT_INVERTED = true,
            RIGHT_INVERTED = false;
#if TEST_ROBOT_MODE == 1
        constexpr float STEPS_PER_MM = 14.8F;
#elif TEST_ROBOT_MODE == 2
        constexpr float STEPS_PER_MM = STEPS_PER_REV / (WHEEL_DIAMETER * 3.14159265359); // 200 steps per revolution / (0.06m * 3.14159265359)
#else
        constexpr float STEPS_PER_MM = STEPS_PER_REV / (WHEEL_DIAMETER * 3.14159265359); // 200 steps per revolution / (0.06m * 3.14159265359)
#endif
        constexpr float MmToStep(float mm)
        {
            return mm * STEPS_PER_MM;
        }
        constexpr float StepToMm(float step)
        {
            return step / STEPS_PER_MM;
        }

    }

}
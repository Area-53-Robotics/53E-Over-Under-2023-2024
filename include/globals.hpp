#pragma once

#include <algorithm>
#include <memory>

#include "api.h"
#include "lemlib/api.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/flaps.hpp"
#include "lib/subsystems/flywheel.hpp"
#include "lib/subsystems/hang.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/logger.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "sylib/sylib.hpp"

// This macro constant controls whether the subsystems send telemetry or not
// #define LOGGING
#define LOGGING_FLYWHEEL_ROUTE 2
#define LOGGING_INTAKE_ROUTE 4

// WARNING: calls to different devices with the same ports will cause the
// program to silently crash

#ifdef LOGGING
inline lib::Logger logger;
#endif

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

inline sylib::Addrled pto_led(22, 42, 20);

// Flaps
inline auto flaps_piston = std::make_shared<pros::ADIDigitalOut>('C');
inline lib::Flaps flaps(flaps_piston);

// PTO
inline pros::ADIAnalogOut pto_piston('A');
inline pros::ADIAnalogOut pto_piston_two('B');

// Intake
inline auto intake_motor = std::make_shared<pros::Motor>(-12);
inline lib::Intake intake(intake_motor);

// Drivetrain
// drive motors
inline pros::Motor lF(1, pros::E_MOTOR_GEAR_BLUE);
inline pros::Motor lM(2, pros::E_MOTOR_GEARSET_06);
inline pros::Motor lB(3, pros::E_MOTOR_GEARSET_06);

inline pros::Motor rF(-8, pros::E_MOTOR_GEARSET_06);
inline pros::Motor rM(-9, pros::E_MOTOR_GEARSET_06);
inline pros::Motor rB(-10, pros::E_MOTOR_GEARSET_06);

// motor groups
inline pros::MotorGroup left_motors({lF, lM, lB});   // left motor group
inline pros::MotorGroup right_motors({rF, rM, rB});  // right motor group

inline lemlib::Drivetrain drivetrain{
    &left_motors,   // left drivetrain motors
    &right_motors,  // right drivetrain motors
    10,             // track width // TODO:  measure this value correctly
    2.75,           // wheel diameter
    600,            // wheel rpm
    8               // chase power
};

inline pros::Imu inertial_sensor(14);

inline lemlib::OdomSensors sensors{
    nullptr,          // vertical tracking wheel 1
    nullptr,          // vertical tracking wheel 2
    nullptr,          // horizontal tracking wheel 1
    nullptr,          // horizontal tracking wheel 2
    &inertial_sensor  // inertial sensor
};

// linear motion controller
inline lemlib::ControllerSettings linear_controller(
    22,    // proportional gain (kP)
    0,     // integral gain (kI)
    10,    // derivative gain (kD)
    3,     // anti windup
    1,     // small error range, in inches
    200,   // small error range timeout, in milliseconds
    2,     // large error range, in inches
    1000,  // large error range timeout, in milliseconds
    5      // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angular_controller(
    2,    // proportional gain (kP)
    0,    // integral gain (kI)
    30,   // derivative gain (kD)
    3,    // anti windup
    1,    // small error range, in degrees
    100,  // small error range timeout, in milliseconds
    3,    // large error range, in degrees
    500,  // large error range timeout, in milliseconds
    10    // maximum acceleration (slew)
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttleCurve(
    3,     // joystick deadband out of 127
    10,    // minimum output where drivetrain will move out of 127
    1.019  // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steerCurve(
    3,     // joystick deadband out of 127
    10,    // minimum output where drivetrain will move out of 127
    1.019  // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, linear_controller,
                               angular_controller, sensors);

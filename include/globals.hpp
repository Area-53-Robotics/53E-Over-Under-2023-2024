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
#include "sylib/sylib.hpp"

// WARNING: calls to different devices with the same ports will cause the
// program to silently crash

inline lib::Logger logger;

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

inline sylib::Addrled led(22, 4, 20);

inline auto flywheel_led = std::make_shared<sylib::Addrled>(22, 6, 10);

// Flywheel
inline sylib::SpeedControllerInfo flywheel_speed_controller(
    [](double rpm) { return 1000; },  // kV function
    0,                                // kP
    0,                                // kI
    0,                                // kD
    0,                                // kH
    false,                            // anti-windup enabled
    0,                                // anti-windup range
    false,                            // p controller bounds threshold enabled
    0,                                // p controller bounds cutoff enabled
    1,                                // kP2 for when over threshold
    0                                 // range to target to apply max voltage
);

inline auto flywheel_motor =
    std::make_shared<sylib::Motor>(4, 600, true, flywheel_speed_controller);

inline lib::Flywheel flywheel(flywheel_motor, flywheel_led);

// Flaps
inline auto flaps_piston = std::make_shared<pros::ADIDigitalOut>('C');
inline lib::Flaps flaps(flaps_piston);

// Hang
inline auto hang_piston = std::make_shared<pros::ADIDigitalOut>('E');
inline lib::Hang hang(hang_piston);

// Intake
inline auto intake_motor = std::make_shared<pros::Motor>(2);
inline lib::Intake intake(intake_motor);

// Drivetrain
inline pros::Motor_Group left_motors({-11, -19, 20});
inline pros::Motor_Group right_motors({1, 8, -9});

inline lemlib::Drivetrain drivetrain{
    &left_motors,   // left drivetrain motors
    &right_motors,  // right drivetrain motors
    10,             // track width // TODO:  measure this value correctly
    4,              // wheel diameter
    342.85,         // wheel rpm
    8               // chase power
};

inline pros::ADIEncoder left_enc('A', 'B', false);
inline pros::ADIEncoder back_enc('G', 'H', false);

inline lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, 3);
inline lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -4);

inline pros::Imu inertial_sensor(16);

inline lemlib::OdomSensors sensors{
    &left_tracking_wheel,  // vertical tracking wheel 1
    nullptr,               // vertical tracking wheel 2
    &back_tracking_wheel,  // horizontal tracking wheel 1
    nullptr,               // horizontal tracking wheel 2
    &inertial_sensor       // inertial sensor
};

// linear motion controller
inline lemlib::ControllerSettings linearController(
    10,   // proportional gain (kP)
    0,    // integral gain (kI)
    35,   // derivative gain (kD)
    3,    // anti windup
    1,    // small error range, in inches
    100,  // small error range timeout, in milliseconds
    3,    // large error range, in inches
    500,  // large error range timeout, in milliseconds
    40    // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angularController(
    2,     // proportional gain (kP)
    0.01,  // integral gain (kI)
    30,    // derivative gain (kD)
    3,     // anti windup
    1,     // small error range, in degrees
    100,   // small error range timeout, in milliseconds
    3,     // large error range, in degrees
    500,   // large error range timeout, in milliseconds
    10     // maximum acceleration (slew)
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, linearController, angularController,
                               sensors);

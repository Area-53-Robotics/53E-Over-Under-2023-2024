#pragma once

#include <algorithm>
#include <memory>

#include "api.h"
#include "lemlib/api.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/flaps.hpp"
#include "lib/subsystems/flywheel.hpp"
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
    [](double rpm) { return 5; },  // kV function
    1,                             // kP
    1,                             // kI
    1,                             // kD
    1,                             // kH
    false,                         // anti-windup enabled
    0,                             // anti-windup range
    false,                         // p controller bounds threshold enabled
    0,                             // p controller bounds cutoff enabled
    1,                             // kP2 for when over threshold
    0                              // range to target to apply max voltage
);

inline auto flywheel_motor =
    std::make_shared<sylib::Motor>(17, 600, true, flywheel_speed_controller);

inline lib::Flywheel flywheel(flywheel_motor, flywheel_led);

// Flaps
inline auto piston = std::make_shared<pros::ADIDigitalOut>('C');
inline lib::Flaps flaps(piston);

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

inline pros::ADIEncoder left_enc('A', 'B', true);
inline pros::ADIEncoder back_enc('G', 'H', true);

// left tracking wheel
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

// lateral motion controller
inline lemlib::ControllerSettings lateralController{
    25,    // kP
    45,    // kD
    1,     // small exit range
    1000,  // small exit timeout
    3,     // large error range
    5000,  // large error timeout
    0,     // slew
};

// angular motion controller
inline lemlib::ControllerSettings angularController{
    3,     // kP
    25,    // kD
    1,     // small exit range
    1000,  // small exit timeout
    3,     // large exit range
    5000,  // large exit timeout
    0,     // slew
};

// create the chassis
inline lemlib::Chassis chassis(drivetrain, lateralController, angularController,
                               sensors);

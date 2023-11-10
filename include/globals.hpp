#pragma once

#include <algorithm>
#include <memory>

#include "api.h"
#include "lemlib/api.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/flaps.hpp"
#include "lib/subsystems/intake.hpp"
#include "pros/adi.hpp"
#include "sylib/sylib.hpp"

// WARNING: calls to different devices with the same ports will cause the
// program to silently crash

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

inline sylib::Addrled led(22, 5, 20);

// Catapult
inline auto catapult_motor = std::make_shared<pros::Motor>(20);
inline auto catapult_rotation_sensor = std::make_shared<pros::Rotation>(8);
inline lib::Catapult catapult(catapult_motor, catapult_rotation_sensor);

// Flaps
inline auto piston = std::make_shared<pros::ADIDigitalOut>('D');
inline lib::Flaps flaps(piston);

// Intake
inline auto intake_motor = std::make_shared<pros::Motor>(9);
inline lib::Intake intake(intake_motor);

// Drivetrain
inline pros::Motor_Group left_motors({-11, -17, 16});
inline pros::Motor_Group right_motors({1, -2, 3});

inline lemlib::Drivetrain_t drivetrain{
    &left_motors,   // left drivetrain motors
    &right_motors,  // right drivetrain motors
    10,             // track width // TODO:  measure this value correctly
    4,              // wheel diameter
    342.85,         // wheel rpm
    8               // chase power
};

inline pros::ADIEncoder left_enc('A', 'B', false);
inline pros::ADIEncoder back_enc('G', 'H', false);

// left tracking wheel
inline lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, 3);
inline lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -4);

inline pros::Imu inertial_sensor(17);

inline lemlib::OdomSensors_t sensors{
    &left_tracking_wheel,  // vertical tracking wheel 1
    nullptr,
    // nullptr,  // vertical tracking wheel 2
    &back_tracking_wheel,  // horizontal tracking wheel 1
    // nullptr,
    nullptr,          // horizontal tracking wheel 2
    &inertial_sensor  // inertial sensor
};

// lateral motion controller
inline lemlib::ChassisController_t lateralController{
    20,    // kP
    40,    // kD
    1,     // small exit range
    1000,  // small exit timeout
    3,     // large error range
    5000,  // large error timeout
};

// angular motion controller
inline lemlib::ChassisController_t angularController{
    5,     // kP
    10,    // kD
    1,     // small exit range
    1000,  // small exit timeout
    3,     // large exit range
    5000,  // large exit timeout
};

// create the chassis
inline lemlib::Chassis chassis(drivetrain, lateralController, angularController,
                               sensors);

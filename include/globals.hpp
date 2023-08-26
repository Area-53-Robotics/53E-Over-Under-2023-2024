#pragma once

#include <algorithm>
#include <memory>

#include "Graphy/Grapher.hpp"
#include "api.h"
#include "lemlib/api.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/intake.hpp"

// WARNING: calls to different devices with the same ports will cause the
// program to silently crash

inline std::shared_ptr<graphy::AsyncGrapher> grapher(
    new graphy::AsyncGrapher("Joystick Output"));


inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

inline auto catapult_motor = std::make_shared<pros::Motor>(
    22);  // WARNING: this motor should be used nowhere else besides here
inline lib::Catapult catapult(catapult_motor);

inline auto intake_motor = std::make_shared<pros::Motor>(
    10);  // WARNING: this motor should be used nowhere else besides here

inline lib::Intake intake(intake_motor);

inline pros::Motor_Group left_motors({-11, 12, -15});
inline pros::Motor_Group right_motors({1, -2, 3});

inline lemlib::Drivetrain_t drivetrain{
    &left_motors,   // left drivetrain motors
    &right_motors,  // right drivetrain motors
    10,             // track width // TODO:  measure this value correctly
    4,              // wheel diameter
    342.85          // wheel rpm
};

inline pros::ADIEncoder left_enc('A', 'B', false);
inline pros::ADIEncoder back_enc('G', 'H', false);

// left tracking wheel
inline lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, 3);
inline lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -4);

inline pros::Imu inertial_sensor(17);

inline lemlib::OdomSensors_t sensors{
    &left_tracking_wheel,  // vertical tracking wheel 1
    nullptr,               // vertical tracking wheel 2
    &back_tracking_wheel,  // horizontal tracking wheel 1
    nullptr,               // horizontal tracking wheel 2
    &inertial_sensor       // inertial sensor
};

// forward/backward PID
inline lemlib::ChassisController_t lateralController{
    8,    // kP
    30,   // kD
    1,    // smallErrorRange
    100,  // smallErrorTimeout
    3,    // largeErrorRange
    500,  // largeErrorTimeout
    5     // slew rate
};

// turning PID
inline lemlib::ChassisController_t angularController{
    4,    // kP
    40,   // kD
    1,    // smallErrorRange
    100,  // smallErrorTimeout
    3,    // largeErrorRange
    500,  // largeErrorTimeout
    0     // slew rate
};

// create the chassis
inline lemlib::Chassis chassis(drivetrain, lateralController, angularController,
                               sensors);
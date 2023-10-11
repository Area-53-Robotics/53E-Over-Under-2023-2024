#include <cmath>

#include "globals.hpp"
#include "main.h"

// TODO: replace with LemLib once pr gets merged:
// https://github.com/LemLib/LemLib/pull/50
double calc_drive_curve(double joy_stick_position, float drive_curve_scale) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  while (true) {
    // Intake Control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      controller.rumble(".");
      intake.set_state(lib::IntakeState::Running);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      controller.rumble(".");
      intake.set_state(lib::IntakeState::Reversed);
    } else {
      intake.set_state(lib::IntakeState::Idle);
    }

    // Flaps control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      printf("expanding\n");
      flaps.set_state(lib::FlapState::Expanded);
    } else {
      flaps.set_state(lib::FlapState::Idle);
    }

    // Catapult control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      controller.rumble(".");
      catapult.fire();
    }

    // Drivetrain control

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + 1;
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) + 1;

    int left_power = calc_drive_curve(left, 3);
    int right_power = calc_drive_curve(right, 3);

    left_motors.move(left_power);  // TODO: handle this with LemLib
    right_motors.move(right_power);

    pros::delay(20);
  }
}

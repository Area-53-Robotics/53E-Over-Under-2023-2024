#include <cmath>

#include "globals.hpp"
#include "lib/subsystems/flywheel.hpp"
#include "lib/subsystems/intake.hpp"
#include "main.h"
#include "pros/misc.h"

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
  printf("opcontrol started\n");
  bool pto_enabled = true;
  bool drive_reversed = false;

  while (true) {
    // Intake Control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intake.set_state(lib::IntakeState::Running);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intake.set_state(lib::IntakeState::Reversed);
    } else {
      intake.set_state(lib::IntakeState::Idle);
    }

    // Flaps control
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      flaps.set_state(lib::FlapState::Expanded);
    } else {
      flaps.set_state(lib::FlapState::Idle);
    }

    // Hang control
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      controller.rumble(".");
      pto_enabled = !pto_enabled;
    }

    if (pto_enabled == false) {
      
      pto_piston_two.set_value(0);
      pto_led.set_all(0x6AF844);
    } else {
      pto_piston_two.set_value(1);
      pto_led.set_all(0xFF5632);
    }

    /*
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      flywheel.set_state(lib::FlywheelState::Reversed);
    } else {
      flywheel.set_state(lib::FlywheelState::Idle);
    }
    */

    // Drivetrain control
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      controller.rumble(".");
      drive_reversed = !drive_reversed;
    }

    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    if (drive_reversed) {
      chassis.tank(-right, -left, 10);
    } else {
      chassis.tank(left, right, 10);
    }

    pros::delay(20);
  }
}

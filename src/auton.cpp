#include <cstdio>
#include "lib/subsystems/catapult.hpp"
#include "globals.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/flaps.hpp"
#include "lib/subsystems/flywheel.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/auton_selector.hpp"
#include "main.h"
#include "pros/rtos.hpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off
 */

// ASSET(to_bar_txt)

void autonomous() {
  switch (lib::selector::auton) {
    case 1: // Offensive side
      flywheel.set_state(lib::FlywheelState::Reversed);
      pros::delay(500);
      flywheel.set_state(lib::FlywheelState::Idle);
      chassis.moveToPoint(0, 35, 1000);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveToPose(-24, 46, -90, 2000);
      intake.set_state(lib::IntakeState::Running);
      pros::delay(2000);
      chassis.turnTo(0, 50, 180, 1000);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.turnTo(-24, 70, -90, 1000);
      chassis.moveToPoint(-24, 70, 1000);
      intake.set_state(lib::IntakeState::Running);
      pros::delay(2000);
      chassis.turnTo(24, 70, 180, 1000);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(1500);
      intake.set_state(lib::IntakeState::Idle);
      flaps.set_state(lib::FlapState::Expanded);
      chassis.moveToPoint(24, 70, 2000);
      chassis.waitUntilDone();
      chassis.moveToPoint(0, 70, 1000, false);
      chassis.waitUntilDone();




      break;
    case 2:  // Defensive
      flywheel.set_state(lib::FlywheelState::Reversed);
      pros::delay(500);
      flywheel.set_state(lib::FlywheelState::Idle);
      chassis.moveToPose(-12, 46, -45, 2000);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveToPoint(-10, 20, 1000, false);
      chassis.turnTo(0, 0, 180, 1000);
      flaps.set_state(lib::FlapState::Expanded);
      pros::delay(1000);
      chassis.moveToPoint(10, 0, 2000);
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveToPose(25, 0, -45, 2000);
      chassis.waitUntilDone();

      
      break;
    case 3:  // Skills
      chassis.setPose(-35, -58, 300);
      // Move to goal
      chassis.moveToPose(35, -59, 90, 5000);
      chassis.moveToPose(18, -1, 90, 4000);
      chassis.moveToPose(42, 0, 90, 3000);
      flaps.set_state(lib::FlapState::Idle);

      break;
    case 4:  // Do nothing
      break;
  }
}

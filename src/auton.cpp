#include "globals.hpp"
#include "lib/utils/auton_selector.hpp"
#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  switch (lib::selector::auton) {
    case 1:  // Left simple
      chassis.moveTo(0, 10, 0, 4000);
      pros::delay(2000);
      chassis.moveTo(0, 0, 0, 4000, false, false);
      /*
      chassis.moveTo(24, 12, 3000);
      intake.set_state(lib::IntakeState::Running);
      chassis.turnTo(72, 12, 2000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveTo(68, 12, 3000);
      */
      // touch the bar with the wiggly antenna.
      break;
    case 2:  // Left with goal
      /*
      chassis.moveTo(24, 12, 3000);
      intake.set_state(lib::IntakeState::Running);
      chassis.turnTo(72, 12, 2000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.turnTo(72, 48, 2000);
      chassis.moveTo(72, 48, 3000);
      intake.set_state(lib::IntakeState::Reversed);
      */
      break;
    case 3:  // Right simple
      /*
      chassis.turnTo(132, 48, 2000);
      chassis.moveTo(132, 48, 3000);
      intake.set_state(lib::IntakeState::Running);
      */
      break;
    case 4:  // Right with extra goal
      /*
      chassis.turnTo(132, 48, 2000);
      chassis.moveTo(132, 48, 3000);
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveTo(72, 48, 3000);
      intake.set_state(lib::IntakeState::Running);
      chassis.turnTo(120, 48, 2000);
      chassis.moveTo(120, 48, 3000);
      intake.set_state(lib::IntakeState::Reversed);
      */
      break;
    case 5:  // Do nothing
      break;
    case 0:  // Skills
      break;
  }
}

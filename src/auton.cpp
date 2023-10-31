#include "globals.hpp"
#include "lib/subsystems/flaps.hpp"
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
    case 1:  // Defensive simple
      chassis.moveTo(6, 9, 50, 4000, false, true, 8, 0.4);
      pros::delay(1000);
      flaps.set_state(lib::FlapState::Expanded);
      pros::delay(1000);
      chassis.turnTo(12, 9, 2000);
      pros::delay(1000);
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveTo(17, 19, 90, 4000, false, true, 8, 0.4);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(2000);
      intake.set_state(lib::IntakeState::Idle);
      pros::delay(500);
      // chassis.moveTo(50, 19, 90, 4000, false, true, 8, 0.4);
      // chassis.moveTo(17, 19, 90, 4000, false, false, 8, 0.4);
      chassis.moveTo(-7, -35, 0, 5000, false, false);

      //  chassis.waitUntilDist(4);
      //  chassis.waitUntilDist(9);
      //    flaps.set_state(lib::FlapState::Idle);
      //      move to bar
      //      chassis.moveTo(-24, 0, 0, 4000);

      // chassis.moveTo(24, 12, 3000);
      // chassis.turnTo(72, 12, 2000);
      // intake.set_state(lib::IntakeState::Idle);
      // chassis.moveTo(68, 12, 3000);
      //  touch the bar with the wiggly antenna.
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

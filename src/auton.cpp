#include <cstdio>

#include "globals.hpp"
#include "lib/subsystems/catapult.hpp"
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
  catapult.set_state(lib::CatapultState::Idle);

  chassis.setPose(-15, 55, 275);

  // Move to goal
  chassis.moveTo(-60, 30, 180, 4000);

  switch (lib::selector::auton) {
    case 1:
      // Offensive side
      // chassis.setPose(-15, 55, 275);

      // Move to goal
      // chassis.moveTo(-60, 30, 180, 4000);

      // Turn on intake
      // intake.set_state(lib::IntakeState::Reversed);

      // Ram into goal
      // chassis.moveTo(-60, 0, 180, 2000);
      // intake.set_state(lib::IntakeState::Idle);

      // Drive back to bar

      break;
    case 2:
      // Defensive

      break;
    case 3:  // Skills
      break;
    case 4:  // Do nothing
      break;
  }
}

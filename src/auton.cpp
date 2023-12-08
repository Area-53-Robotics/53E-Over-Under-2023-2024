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
      chassis.moveTo(-5, 45, 0, 2000);
      chassis.turnTo(10, 45, 3000);
      chassis.moveTo(20, 45, 110, 2000);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(3000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveTo(-5, 45, 90, 3000, false);
      chassis.moveTo(-35, 15, 270, 3000);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);
      chassis.waitUntilDone();
      //chassis.moveTo(5, 45, 270, 2000, false);
      //chassis.moveTo(20, 45, 90, 2000);
      //chassis.waitUntilDone();
      
      

      //flywheel.set_state(lib::FlywheelState::Spinning);
      //pros::delay(300);
      //flywheel.set_state(lib::FlywheelState::Idle);
     /* chassis.moveTo(0, 10, 0, 4000);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);
      pros::delay(500);
      chassis.moveTo(2, -14, 7, 1000, false);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveTo(11, 34, 0, 3000);
      chassis.moveTo(25, 25, 90, 4000);
      flaps.set_state(lib::FlapState::Expanded);
      chassis.waitUntilDone();
      */

      break;
    case 3:  // Skills
      chassis.setPose(-35, -58, 300);
      // Move to goal
      chassis.moveTo(-50, -50, 45, 4000, false); 
      chassis.moveTo(35, -59, 90, 5000);
      chassis.moveTo(18, -1, 90, 4000);
      flaps.set_state(lib::FlapState::Expanded);
      chassis.moveTo(42, 0, 90, 3000);
      flaps.set_state(lib::FlapState::Idle);

      break;
    case 4:  // Do nothing
      break;
  }
}
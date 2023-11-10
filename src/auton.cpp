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
  printf("starting movement\n");
  chassis.moveTo(0, 10, 0, 8000);
  printf("ended movement\n");

  switch (lib::selector::auton) {
    case 1:  // Defensive simple
      /*
      // deploy the intake
      chassis.moveTo(0, 10, 0, 0);
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(500);
      intake.set_state(lib::IntakeState::Idle);
      pros::delay(500);

      // move to the match load
      chassis.moveTo(6, 9, 50, 4000);
      pros::delay(50);
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
      // move to touch the bar
      chassis.moveTo(-7, -35, 0, 5000, false, false);
      */

      break;
    case 2:
      // Offensive Simple
      printf("starting auton\n");
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(500);
      intake.set_state(lib::IntakeState::Idle);
      pros::delay(500);
      printf("started movement\n");
      chassis.moveTo(-19, 25, -90, 4000);
      printf("finished movement\n");
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveTo(-50, 25, -90, 4000);
      intake.set_state(lib::IntakeState::Idle);
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
    case 3:  // Skills
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(500);
      intake.set_state(lib::IntakeState::Idle);
      pros::delay(500);

      catapult.set_state(lib::CatapultState::Repeating);

      pros::delay(50000);

      catapult.set_state(lib::CatapultState::Loading);

      chassis.tank(127, 127);

      /*
      chassis.turnTo(132, 48, 2000);
      chassis.moveTo(132, 48, 3000);
      intake.set_state(lib::IntakeState::Running);
      */
      break;
    case 4:  // Do nothing
      break;
    case 5:  // Ram
      chassis.tank(127, 127);
      intake.set_state(lib::IntakeState::Reversed);
      break;
  }
}

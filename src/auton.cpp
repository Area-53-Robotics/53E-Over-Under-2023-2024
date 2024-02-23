#include <cstdio>

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
    case 1:  // Offensive side
      printf("offensive side\n");

      hang.set_state(lib::HangState::Expanded);  // Release Intake
      chassis.moveToPoint(0, 35, 2000);          // Move In front Of goal
      chassis.waitUntilDone();
      chassis.turnTo(20, 45, 1000);                  // turn to goal
      intake.set_state(lib::IntakeState::Reversed);  // outtake preload triball
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.turnTo(-30, 29, 1000);  // turn to middle bar triball
      chassis.moveToPoint(-30, 25, 2000);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running);  // intake middle bar triball
      chassis.turnTo(0, 48, 2000);                  // turn towards goal
      chassis.moveToPoint(-20, 40, 1000);
      intake.set_state(lib::IntakeState::Reversed);  // outake middle bar
                                                     // triball
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveToPoint(-40, 47, 1000);  // move to middle middle bar triball
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running);  // intake this triball
      pros::delay(2000);
      chassis.turnTo(30, 45, 1000);  // turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);  // expand flaps
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(500);
      chassis.moveToPoint(14, 48, 2000);  // push in all four triballs
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);

      /*
      //offensive w 9080c
      hang.set_state(lib::HangState::Expanded);
      chassis.moveToPoint(0, 48, 3000);
      chassis.turnTo(-20, 48, 2000);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveToPoint(-25, 44, 1000);
      chassis.moveToPoint(0, 44, 2000, false);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      */

      break;
    case 2:  // Defensive
      printf("Defensive side\n");
      // winpoint code
      hang.set_state(lib::HangState::Expanded);  // Release Intake
      pros::delay(2000);
      chassis.turnTo(-45, 45, 1000);
      chassis.moveToPoint(-10, 10, 1000);  // unload triball from matchload zone
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);
      chassis.moveToPoint(8, 0, 2000, false);  // move to starting points
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveToPoint(-10, -10,
                          1500);  // move back to start don't ask why its -10 bc
                                  // the bot wasnt cooperating :/
      chassis.waitUntilDone();
      chassis.turnTo(36, -15, 1000);  // turn to bar
      pros::delay(2000);
      chassis.moveToPoint(30, -8, 1000);  // touch bar w ziptie

      break;
    case 0:  // Skills
      printf("Skills\n");
      hang.set_state(lib::HangState::Expanded);
      chassis.moveToPoint(-20, 0, 1000);
      chassis.turnTo(24, 24, 1000);
      chassis.moveToPoint(-17, 0, 1000,
                          false);  // back into zone for matchloading
      chassis.waitUntilDone();
      flywheel.set_state(
          lib::FlywheelState::Spinning);  // spin flywheel while touching match
                                          // load zone
      pros::delay(30000);
      chassis.waitUntilDone();
      hang.set_state(lib::HangState::Idle);
      flywheel.set_state(lib::FlywheelState::Idle);
      chassis.turnTo(0, -6, 1000);
      chassis.moveToPoint(0, -6, 2000);  // move back to starting point
      chassis.waitUntilDone();
      chassis.turnTo(60, 0, 1000);       // turn towards other side
      chassis.moveToPoint(75, 0, 4000);  // move under bar to other side
      chassis.turnTo(88, 45, 1000);      // turn to goal
      chassis.waitUntilDone();
      chassis.moveToPose(91, 34, -90, 1500);  // push into goal from side
      chassis.waitUntilDone();
      chassis.moveToPose(88, 5, 0, 2000, {.forwards = false});  // move
                                                                // backwards
      chassis.moveToPose(88, 50, 0, 2000);  // push into goal from side
      chassis.moveToPose(88, 0, 0, 2000, {.forwards = false});  // move
                                                                // backwards
      chassis.turnTo(55, 40, 1000);
      chassis.moveToPoint(55, 45, 3000);  // move to middle bar
      chassis.turnTo(85, 45, 1000);       // face goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);  // open wings
      chassis.moveToPoint(85, 45, 2000);          // push into goal
      chassis.moveToPoint(50, 45, 2000, false);   // move back
      flaps.set_state(lib::FlapState::Idle);      // close wings
      chassis.moveToPoint(60, 70, 2000);  // move left to other side of goal
      chassis.turnTo(70, 70, 1000);       // turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);  // open wings
      chassis.moveToPoint(75, 70, 2000);          // push into goal
      chassis.waitUntilDone();
      chassis.moveToPoint(60, 65, 1500, false);

      /*
      chassis.moveToPoint(60, 55, 200
      0, false);
      flaps.set_state(lib::FlapState::Idle);
      chassis.turnTo(55, 75, )
      */

      break;
    case 3:  // Do nothing
      printf("nothing\n");
      break;
  }
}

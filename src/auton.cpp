#include <cstdio>

#include "globals.hpp"
#include "lib/subsystems/catapult.hpp"
#include "lib/subsystems/flaps.hpp"
#include "lib/subsystems/flywheel.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/auton_selector.hpp"
#include "main.h"
#include "pros/rtos.hpp"

ASSET(first_txt);
ASSET(sixballend_txt);

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
// ASSET(path_jerryio_txt)
// chassis.follow(path_jerryio_txt, 15, 5000);

void autonomous() {
  switch (lib::selector::auton) {
    case 1:  // Offensive side
      printf("offensive side\n");
      chassis.moveToPoint(0, 10, 3000);
      /*
      flaps.set_state(lib::FlapState::Expanded);
      chassis.turnToPoint(-32, 52, 1000);
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveToPoint(-35, 50, 2000);//move to middle triball
      chassis.waitUntilDone();

      chassis.turnToPoint(25, 45, 1000);//turn to goal
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Reversed);
      flaps.set_state(lib::FlapState::Expanded);
      chassis.moveToPoint(25, 45, 2000);//push into goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      intake.set_state(lib::IntakeState::Running);
      chassis.moveToPoint(-30, 27, 1500);//intake left middle triball
      chassis.waitUntilDone();
      chassis.turnToPoint(25, 40, 1000);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveToPoint(25, 40, 2000);
      chassis.waitUntilDone();
      chassis.moveToPoint(0, 9, 1000);//move to start
      chassis.waitUntilDone();
      chassis.turnToPoint(15, 25, 800);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Reversed);//outtkae triball next to
      side goal pros::delay(800); chassis.waitUntilDone();
      chassis.moveToPoint(0, -9, 900);//move to start start
      chassis.waitUntilDone();
      chassis.turnToPoint(-36, -7, 900);//move under bar
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running);
      chassis.moveToPoint(-40, -7, 1800);//move under bar
      chassis.waitUntilDone();
      chassis.moveToPoint(5, -3, 1800, {.forwards=false});//move back to start
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);
      chassis.turnToPoint(15, 25, 800);
      chassis.waitUntilDone();
      chassis.setPose(34, -62, 500);      chassis.moveToPoint(5, -3, 1800,
      {.forwards=false});//move back to start chassis.follow(sixballend_txt, 14,
      2500);//push into side goal chassis.waitUntilDone();
      chassis.moveToPoint(5, 15, 1000, {.forwards=false});
*/

      /*
      FOUR BALL AUTONOMOUS
      intake.set_state(lib::IntakeState::Running);
      pros::delay(1000);
      chassis.moveToPoint(-4, 35, 1500);          // Move In front Of goal
      chassis.waitUntilDone();
      chassis.turnTo(20, 40, 800);                  // turn to goal
      intake.set_state(lib::IntakeState::Reversed);  // outtake preload triball
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.turnTo(-30, 29, 900);  // turn to middle bar triball
      chassis.waitUntilDone();
      chassis.moveToPoint(-30, 25, 1500);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running);  // intake middle bar triball
      chassis.turnTo(0, 39, 1500);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Reversed);  // outake middle bar
      pros::delay(1500);
      chassis.waitUntilDone();           // turn towards goal
      chassis.moveToPoint(-20, 40, 1000);
      intake.set_state(lib::IntakeState::Running);
      chassis.moveToPoint(-40, 49, 1000);  // move to middle middle bar triball
      chassis.waitUntilDone();
      chassis.turnTo(30, 43, 1000);  // turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);  // expand flaps
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveToPoint(14, 39, 2000);  // push in all four triballs
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      */

      break;
    case 2:  // Defensive
      printf("Defensive side\n");
      // winpoint code ,,kl.'-[]=      chassis.moveToPoint(0, 10, 3000);

      chassis.turnToPoint(-45, 45, 1000);
      chassis.moveToPoint(-12, 10, 1000);  // unload triball from matchload zone
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Expanded);
      chassis.moveToPoint(8, 0, 2000,
                          {.forwards = false});  // move to starting points
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Idle);
      chassis.moveToPoint(-10, -5,
                          1500);  // move back to start don't ask why its -10 bc
      chassis.waitUntilDone();
      chassis.turnToPoint(36, -4, 1000);  // turn to bar
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Reversed);  // outtake matchload
                                                     // triball
      pros::delay(1500);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Idle);  // set intake state to idle
      chassis.turnToPoint(36, 47, 1000);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running);
      chassis.moveToPoint(36, 53, 2000);  // move to middle triball and intake
      chassis.waitUntilDone();
      chassis.turnToPoint(0, -5, 1000);
      chassis.moveToPoint(0, -5, 2500);  // move back to starting point
      chassis.waitUntilDone();
      chassis.turnToPoint(36, -5, 1000);  // turn to bar
      pros::delay(2000);
      intake.set_state(lib::IntakeState::Reversed);
      chassis.moveToPoint(36, -5, 1000);  // touch bar w ziptie

      break;
    case 0:  // Skills
      printf("Skills\n");
      intake.set_state(lib::IntakeState::Running);
      pros::delay(1000);
      // hang.set_state(lib::HangState::Expanded);
      chassis.moveToPoint(-20, 0, 1000);
      chassis.turnToPoint(24, 17, 1000);
      chassis.moveToPoint(
          -17, 0, 1000,
          {.forwards = false});  // back into zone for matchloading
      chassis.waitUntilDone();
      // flywheel.set_state(lib::FlywheelState::Spinning);  // spin flywheel
      // while touching match load zone
      pros::delay(30000);
      chassis.waitUntilDone();
      // hang.set_state(lib::HangState::Idle);
      intake.set_state(lib::IntakeState::Idle);
      // flywheel.set_state(lib::FlywheelState::Idle);
      chassis.moveToPoint(0, -9, 1700);
      chassis.waitUntilDone();
      chassis.turnToPoint(60, -2, 1000);
      chassis.waitUntilDone();
      chassis.moveToPoint(80, -6, 4000);
      chassis.waitUntilDone();
      intake.set_state(
          lib::IntakeState::Reversed);    // move under bar to other side
      chassis.turnToPoint(90, 45, 1000);  // turn to goal
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Expanded);
      chassis.turnToPoint(97, 34, 1000);
      chassis.waitUntilDone();
      chassis.moveToPose(100, 60, -90, 1500);  // push into goal from side
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Idle);  // turn towards other side
      chassis.moveToPose(94, 0, 0, 2000, {.forwards = false});  // move
      chassis.tank(127, 127);
      chassis.moveToPose(98, 59, 0, 2000);  // push into goal from side
      chassis.moveToPose(90, 0, 0, 2000, {.forwards = false});  // move
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Idle);
      intake.set_state(lib::IntakeState::Idle);
      chassis.turnToPoint(55, 40, 1000);
      chassis.moveToPoint(55, 32, 2000);  // move to middle bar
      chassis.waitUntilDone();
      chassis.turnToPoint(85, 45, 1000);  // face goal
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Expanded);               // open wings
      chassis.moveToPoint(85, 45, 2000);                       // push into goal
      chassis.moveToPoint(50, 45, 2000, {.forwards = false});  // move back
      horizontal_wings.set_state(lib::FlapState::Idle);                   // close wings
      chassis.moveToPoint(60, 70, 2000);  // move left to other side of goal
      chassis.turnToPoint(70, 70, 1000);  // turn to goal
      chassis.waitUntilDone();
      horizontal_wings.set_state(lib::FlapState::Expanded);  // open wings
      chassis.moveToPoint(90, 64, 2000);          // push into goal
      chassis.waitUntilDone();
      chassis.moveToPoint(50, 65, 1500, {.forwards = false});
      chassis.waitUntilDone();
      chassis.moveToPoint(90, 64, 2000);
      chassis.waitUntilDone();
      chassis.moveToPoint(60, 65, 1500, {.forwards = false});
      chassis.moveToPoint(60, 55, 2000);
      horizontal_wings.set_state(lib::FlapState::Idle);
      chassis.turnToPoint(55, 75, 0, {.forwards = false});
      break;
    case 3:  // Do nothing
      printf("nothing\n");
      break;
  }
}

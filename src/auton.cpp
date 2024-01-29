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
     
      hang.set_state(lib::HangState::Expanded); //Release Intake
      pros::delay(2000);
      chassis.moveToPoint(0, 35, 2000); //Move In front Of goal
      chassis.waitUntilDone();
      chassis.turnTo(20, 45, 1000); //turn to goal
      intake.set_state(lib::IntakeState::Reversed); //outtake preload triball
      pros::delay(1000);
      chassis.turnTo(-30,25, 1000); //turn to middle bar triball 
      chassis.moveToPoint(-30, 23, 2000);
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running); //intake middle bar triball
      chassis.turnTo(0, 48, 2000); //turn towards goal
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Reversed); //outake middle bar triball 
      pros::delay(1000);
      intake.set_state(lib::IntakeState::Idle);
      chassis.moveToPoint(-40, 48,1000); //move to middle middle bar triball
      chassis.waitUntilDone();
      intake.set_state(lib::IntakeState::Running); //intake this triball
      pros::delay(2000);
      chassis.turnTo(30, 45, 1000); //turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded); //expand flaps
      intake.set_state(lib::IntakeState::Reversed);
      pros::delay(500);
      chassis.moveToPoint(24, 48, 3000); //push in all four triballs 
      chassis.moveToPoint(10, 48, 1000, false); //move backwards 
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
    //winpoint code 
      hang.set_state(lib::HangState::Expanded); //Release Intake
      pros::delay(2000);
      flaps.set_state(lib::FlapState::Expanded);
      pros::delay(2000);
      chassis.moveToPoint(0, 25, 1000); //unload triball from matchload zone
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);
      chassis.moveToPoint(0, 0, 2000, false); //move to starting point
      chassis.turnTo(36, -35, 1000);
      pros::delay(2000);
      chassis.moveToPoint(36, -35, 390); //touch bar w ziptie

      

      break;
    case 3:  // Skills
    
      hang.set_state(lib::HangState::Expanded);  
      chassis.moveToPoint(-20, 0, 1000);
      chassis.turnTo(24, 24, 1000);
      chassis.moveToPoint(-20, 0, 1000, false); //back into zone for matchloading
      chassis.waitUntilDone();
      flywheel.set_state(lib::FlywheelState::Spinning);
      pros::delay(30000);
      chassis.waitUntilDone();
      hang.set_state(lib::HangState::Idle);
      chassis.moveToPoint(0, 0, 2000);//move back to starting point
      chassis.waitUntilDone();
      chassis.turnTo(60, 0, 1000);//turn towards other side
      chassis.moveToPoint(70, 0, 4000);//move under bar to other side
      chassis.turnTo(80, 45, 1000);//turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);//open wings
      chassis.moveToPoint(82, 30, 2000);//push into goal from side
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Idle);//close flaps
      chassis.moveToPoint(80, 10, 2000, false);//move backwards
      chassis.moveToPoint(55, 45, 3000); //move to middle bar 
      chassis.turnTo(85, 45, 1000);//face goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);//open wings
      chassis.moveToPoint(85, 45, 2000);//push into goal
      chassis.moveToPoint(60, 45, 2000, false);//move back
      flaps.set_state(lib::FlapState::Idle);//close wings
      chassis.moveToPoint(60, 50, 2000);//move left to other side of goal
      chassis.turnTo(70, 48, 1000); //turn to goal
      chassis.waitUntilDone();
      flaps.set_state(lib::FlapState::Expanded);//open wings
      chassis.moveToPoint(85, 48, 2000);//push into goal





      break;
    case 4:  // Do nothing
      break;
  }
}

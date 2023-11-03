#include <cstdio>
#include <vector>

#include "globals.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/auton_selector.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "sylib/system.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  // pros::lcd::initialize();
  lib::selector::init();
  sylib::initialize();
  chassis.calibrate();

  catapult.start_task();
  intake.start_task();
  flaps.start_task();

  led.gradient(0x00FF00, 0x0000FF);

  /*
  pros::Task screenTask([=]() {
    while (true) {
      pros::lcd::print(0, "X: %f", chassis.getPose().x);
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
      pros::delay(50);
    }
  });
  //*/

  // pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

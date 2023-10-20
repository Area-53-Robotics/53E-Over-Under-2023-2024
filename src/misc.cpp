#include <cstdio>
#include <vector>

#include "globals.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/auton_selector.hpp"
#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  // pros::lcd::initialize();
  lib::selector::init();
  chassis.calibrate();

  catapult.start_task();
  intake.start_task();
  flaps.start_task();

  // pros::screen::set_pen(pros::Color::black);
  // pros::screen::fill_rect(0, 0, 400, 200);
  // pros::screen::set_pen(pros::Color::red);
  // pros::screen::print(TEXT_MEDIUM, 1, "MANKIND IS DEAD");
  // pros::screen::print(TEXT_MEDIUM, 2, "BLOOD IS FUEL");
  // pros::screen::print(TEXT_MEDIUM, 3, "HELL IS FULL");
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
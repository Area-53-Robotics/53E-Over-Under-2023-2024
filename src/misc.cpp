#include <cstdio>
#include <vector>

#include "globals.hpp"
#include "lib/subsystems/flywheel.hpp"
#include "lib/subsystems/intake.hpp"
#include "lib/utils/auton_selector.hpp"
#include "lib/utils/logger.hpp"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "sylib/system.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  //pros::lcd::initialize();
  lib::selector::init();

  flywheel.set_state(lib::FlywheelState::Idle);
  sylib::initialize();
  chassis.calibrate();

  flywheel.start_task();
  flywheel.set_rate(50);
  intake.start_task();
  flaps.start_task();
  hang.start_task();
  ptoPistonTwo.set_value(1);

#ifdef LOGGING
  logger.start_task();
  logger.set_rate(10);
  logger.set_state(lib::LoggerMode::FirstInFirstOut);
#endif

  led.gradient(0x8B3AFD, 0x7DFF29, 0, 0, false, true);
  led.cycle(*led, 1);

/*
  
  pros::Task screenTask([=]() {
    while (true) {
      pros::lcd::print(0, "X: %f", chassis.getPose().x);
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
      pros::delay(50);
    }
  });
  
  */
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

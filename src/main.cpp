#include "main.h"

#include <cstdio>
#include <vector>

#include "lib/subsystems/catapult.hpp"
#include "pros/apix.h"
#include "pros/colors.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::Motor_Group left_motors({-11, 12, -15});
pros::Motor_Group right_motors({1, -2, 3});

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // lib::Catapult my_catapult;
  //   my_catapult.start_task();

  pros::c::serctl(SERCTL_DISABLE_COBS, nullptr);
  pros::c::serctl(SERCTL_DEACTIVATE, 0x0);

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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

double calc_drive_curve(double joy_stick_position, float drive_curve_scale) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}

void opcontrol() {
  while (true) {
    int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + 1;
    int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) + 1;

    int left_power = calc_drive_curve(left, 3);
    int right_power = calc_drive_curve(right, 3);

    left_motors.move(left_power);
    right_motors.move(right_power);

    pros::delay(20);
  }
}

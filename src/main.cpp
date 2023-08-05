#include "main.h"

#include <vector>

#include "pros/colors.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::screen::set_pen(pros::Color::black);
  pros::screen::fill_rect(0, 0, 400, 200);
  pros::screen::set_pen(pros::Color::red);
  pros::screen::print(TEXT_MEDIUM, 1, "MANKIND IS DEAD");
  pros::screen::print(TEXT_MEDIUM, 2, "BLOOD IS FUEL");
  pros::screen::print(TEXT_MEDIUM, 3, "HELL IS FULL");
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
void opcontrol() {
  pros::MotorGroup left_motors({1, -2, 3});
  pros::MotorGroup right_motors({-11, -12, 14});
  pros::Controller controller(pros::E_CONTROLLER_MASTER);
  int start_time = pros::millis();
  int end_time = start_time + 1000 * 60;

  while (pros::millis() < end_time) {
    // Move the motors at maximum speed
    if (!controller.get_digital(
            pros::E_CONTROLLER_DIGITAL_A)) {  // Emergency stop
      left_motors.move(127);
      right_motors.move(127);
    }

    std::vector<std::int32_t> left_motor_draw =
        left_motors.get_current_draw_all();
    std::vector<std::int32_t> right_motor_draw =
        right_motors.get_current_draw_all();

    std::vector<double> left_motor_temps = left_motors.get_temperature_all();
    std::vector<double> right_motor_temps = right_motors.get_temperature_all();

    // Print data to stdout in csv format
    printf("%i, %i, %i, %i, %i, %i, %f, %f, %f, %f, %f, %f, %i \n",
           left_motor_draw[0], left_motor_draw[1], left_motor_draw[2],
           right_motor_draw[0], right_motor_draw[1], right_motor_draw[2],
           left_motor_temps[0], left_motor_temps[1], left_motor_temps[2],
           right_motor_temps[0], right_motor_temps[1], right_motor_temps[2],
           pros::millis());
    pros::delay(50);  // The brain terminal cannot handle faster than this
  }
}

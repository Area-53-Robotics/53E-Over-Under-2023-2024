#include "lib/subsystems/catapult.hpp"

#include <cstdio>

#include "pros/rtos.hpp"

namespace lib {

Catapult::Catapult(std::shared_ptr<pros::Motor> i_motor) : motor(i_motor){};
Catapult::~Catapult(){};
void Catapult::loop() {
  while (true) {
    if (get_state() == CatapultState::Idle) {
      printf("just chillin\n");
    }
    pros::delay(20);
  }
};
}  // namespace lib


#include "lib/subsystems/intake.hpp"

#include <cstdio>
#include <memory>

#include "api.h"

namespace lib {

Intake::Intake(std::shared_ptr<pros::Motor> i_motor) : motor(i_motor){};

Intake::~Intake(){};

void Intake::loop() {
  while (true) {
    if (get_state() == IntakeState::Idle) {
      printf("just chillin\n");
    } else if (get_state() == IntakeState::Running) {
      motor->move(127);
    }
    pros::delay(20);
  }
};
}  // namespace lib

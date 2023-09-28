#include "lib/subsystems/intake.hpp"

#include <cstdio>
#include <memory>

#include "api.h"

namespace lib {

Intake::Intake(std::shared_ptr<pros::Motor> i_motor) : motor(i_motor){};

void Intake::loop() {
  if (get_state() == IntakeState::Idle) {
    motor->move(0);
  } else if (get_state() == IntakeState::Running) {
    motor->move(127);
  } else if (get_state() == IntakeState::Reversed) {
    motor->move(-127);
  }
};
}  // namespace lib

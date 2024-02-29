#include "lib/subsystems/intake.hpp"

#include <cstdio>
#include <memory>

#include "api.h"
#include "fmt/core.h"
#include "globals.hpp"

namespace lib {

Intake::Intake(std::shared_ptr<pros::Motor> i_motor) : motor(i_motor){};

void Intake::loop() {

#ifdef LOGGING
  logger.telemetry(
      fmt::format("{},{},{}", LOGGING_INTAKE_ROUTE, motor->get_power(), motor->get_temperature()));
#endif

  if (get_state() == IntakeState::Idle) {
    motor->move(0);
  } else if (get_state() == IntakeState::Running) {
    motor->move(127);
  } else if (get_state() == IntakeState::Reversed) {
    motor->move(-127);
  }
};
}  // namespace lib

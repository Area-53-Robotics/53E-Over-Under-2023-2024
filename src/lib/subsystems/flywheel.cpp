#include "lib/subsystems/flywheel.hpp"

#include <cstdio>
#include <memory>

#include "sylib/sylib.hpp"
namespace lib {
Flywheel::Flywheel(std::shared_ptr<sylib::Motor> i_motor) { motor = i_motor; };

void Flywheel::loop() {
  switch (get_state()) {
    case FlywheelState::Idle:
      motor->stop();
      break;
    case FlywheelState::Spinning:
      motor->set_velocity_custom_controller(600);
      break;
  }
}
void Flywheel::toggle() {
  if (!(get_state() == FlywheelState::Spinning)) {
    set_state(FlywheelState::Spinning);
  } else {
    set_state(FlywheelState::Idle);
  }
}

}  // namespace lib

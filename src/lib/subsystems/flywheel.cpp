#include "lib/subsystems/flywheel.hpp"

#include <cstdio>
#include <memory>

#include "sylib/motor.hpp"
#include "sylib/sylib.hpp"
namespace lib {
Flywheel::Flywheel(std::shared_ptr<sylib::Motor> i_motor,
                   std::shared_ptr<sylib::Addrled> i_led) {
  motor = i_motor;
  led = i_led;
};

constexpr int RED = 0xff0000;
constexpr int GREEN = 0x00ff00;

void Flywheel::loop() {
  if (motor->get_velocity_error() > 50) {
    led->set_all(RED);
  } else {
    led->set_all(GREEN);
  }
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

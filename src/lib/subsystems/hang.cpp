#include "lib/subsystems/hang.hpp"

#include <cstdio>
namespace lib {
Hang::Hang(std::shared_ptr<pros::ADIDigitalOut> i_piston) {
  piston = i_piston;
};

void Hang::loop() {
  switch (get_state()) {
    case HangState::Expanded:
      piston->set_value(true);
      break;
    case HangState::Idle:
      piston->set_value(false);
      break;
  }
}

void Hang::toggle() {
  if (!(get_state() == HangState::Expanded)) {
    set_state(HangState::Expanded);
  } else {
    set_state(HangState::Idle);
  }
}

}  // namespace lib
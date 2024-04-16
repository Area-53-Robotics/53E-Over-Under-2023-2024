#include "lib/subsystems/flaps.hpp"

#include <cstdio>
namespace lib {
Flaps::Flaps(std::shared_ptr<pros::ADIDigitalOut> i_piston) {
  piston = i_piston;
};

void Flaps::loop() {
  switch (get_state()) {
    case FlapState::Expanded:
      piston->set_value(true);
      break;
    case FlapState::Idle:
      piston->set_value(false);
      break;
  }
}

void Flaps::toggle() {
  if (!(get_state() == FlapState::Expanded)) {
    set_state(FlapState::Expanded);
  } else {
    set_state(FlapState::Idle);
  }
}

}  // namespace lib

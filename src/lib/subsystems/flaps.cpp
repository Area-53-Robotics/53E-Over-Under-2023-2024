#include "lib/subsystems/flaps.hpp"

#include <cstdio>
namespace lib {
Flaps::Flaps(std::shared_ptr<pros::ADIDigitalOut> i_piston) {
  piston = i_piston;
};

void Flaps::loop() {
  printf("looping\n");
  switch (get_state()) {
    case FlapState::Expanded:
      piston->set_value(true);
      break;
    case FlapState::Idle:
      printf("idling\n");
      piston->set_value(false);
      break;
  }
}

}  // namespace lib

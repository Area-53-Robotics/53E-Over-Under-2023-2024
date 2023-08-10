#include "lib/subsystems/catapult.hpp"

namespace lib {

void Catapult::loop() {
  if (current_state == State::Idle) {
    printf("Just chillin\n");
  }
}

}  // namespace lib

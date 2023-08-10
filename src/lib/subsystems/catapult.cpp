#include "lib/subsystems/catapult.hpp"

#include <cstdio>

namespace lib {

Catapult::Catapult(){};
Catapult::~Catapult(){};
void Catapult::loop() {
  if (get_state() == CatapultState::Idle) {
    printf("just chillin\n");
  }
};
}  // namespace lib

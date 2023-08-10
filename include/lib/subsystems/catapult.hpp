#pragma once
#include <cstdio>

#include "lib/utils/state_machine.hpp"

namespace lib {

enum class State { Idle, Loading, Ready, Firing };
class Catapult : public StateMachine<State> {
 public:
  Catapult();
  ~Catapult();

  void loop() override;
};

}  // namespace lib

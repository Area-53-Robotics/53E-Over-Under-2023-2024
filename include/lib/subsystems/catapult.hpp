#pragma once
#include "lib/utils/state_machine.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class CatapultState { Idle, Loading, Ready, Firing };

class Catapult : public lib::StateMachine<CatapultState> {
 public:
  Catapult();
  ~Catapult();

 private:
 protected:
  void loop() override;
};

}  // namespace lib

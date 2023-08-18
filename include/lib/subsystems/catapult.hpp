#pragma once
#include "lib/utils/state_machine.hpp"
#include "lib/utils/task_wrapper.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class CatapultState { Idle, Loading, Ready, Firing };

class Catapult : public lib::StateMachine<CatapultState>, public TaskWrapper {
 public:
  Catapult();
  ~Catapult();

 private:
 protected:
  void loop() override;
};

}  // namespace lib

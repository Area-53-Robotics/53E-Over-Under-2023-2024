#pragma once

#include "api.h"
#include "lib/utils/state_machine.hpp"
#include "lib/utils/task_wrapper.hpp"

namespace lib {

enum class FlapState { Expanded, Idle };

class Flaps : public StateMachine<FlapState>, public TaskWrapper {
 public:
  Flaps(std::shared_ptr<pros::ADIDigitalOut> piston);

 private:
  std::shared_ptr<pros::ADIDigitalOut> piston;
  void loop() override;
};
}  // namespace lib

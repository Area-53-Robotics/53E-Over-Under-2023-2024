#pragma once

#include "api.h"
#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp"

namespace lib {

enum class HangState { Expanded, Idle };

class Hang : public StateMachine<HangState>, public TaskWrapper {
 public:
  Hang(std::shared_ptr<pros::ADIDigitalOut> piston);

  void toggle();

 private:
  std::shared_ptr<pros::ADIDigitalOut> piston;
  void loop() override;
};
}  // namespace lib

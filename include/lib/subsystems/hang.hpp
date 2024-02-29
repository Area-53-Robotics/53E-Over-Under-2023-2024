#pragma once

#include "api.h"
#include "lib/utils/state_machine.hpp"
#include "lib/utils/task_wrapper.hpp"

namespace lib {

enum class HangState { Expanded, Idle, Boosted };

class Hang : public StateMachine<HangState>, public TaskWrapper {
 public:
  Hang(std::shared_ptr<pros::ADIDigitalOut> piston, std::shared_ptr<pros::ADIDigitalOut> extra_piston);

  void toggle();

 private:
  std::shared_ptr<pros::ADIDigitalOut> piston;
  std::shared_ptr<pros::ADIDigitalOut> extra_piston; 
  void loop() override;
};
}  // namespace lib

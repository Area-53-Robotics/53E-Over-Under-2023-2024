#pragma once

#include <algorithm>

#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class IntakeState { Idle, Running, Reversed };

class Intake : public StateMachine<IntakeState>, public TaskWrapper {
 public:
  Intake(std::shared_ptr<pros::Motor> intake_motor);
  ~Intake();

  void loop() override;

 private:
  std::shared_ptr<pros::Motor> motor;
};
}  // namespace lib

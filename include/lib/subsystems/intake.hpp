#pragma once

#include "lib/utils/state_machine.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class State {
  Idle,
  Running,
  Reversed,
};

class Intake : public StateMachine<State> {
 public:
  Intake(int motor_port);
  ~Intake();

  void loop();

 private:
  pros::Motor motor;
};
}  // namespace lib

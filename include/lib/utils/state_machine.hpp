#pragma once
#include "pros/rtos.hpp"

namespace lib {

template <class State, State initState = State::Idle>
class StateMachine {
 public:
  State get_state() { return current_state; };
  void set_state(State new_state) { current_state = new_state; };
  virtual void loop() = 0;
  void start_loop();

 private:
  State current_state;
  pros::Mutex state_lock;
  pros::Task task{nullptr};
};
};  // namespace lib

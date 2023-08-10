#pragma once
#include "pros/rtos.hpp"

namespace lib {

template <class State>
class StateMachine {
 public:
  State get_state();
  void set_state(State new_state);
  virtual void loop() = 0;
  void start_loop();

  State current_state;

 protected:
 private:
  pros::Mutex state_lock;
  pros::Task* task{nullptr};
};
};  // namespace lib

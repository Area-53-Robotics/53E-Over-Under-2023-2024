// Credit to Ryan:
// https://github.com/Ryan4253/RaidZeroLib/blob/bb9f94f087cae19f22a3d8048642b198f45b7fa1/include/RaidZeroLib/Utility/StateMachine.hpp#L1
// Inspired by:
// https://theol0403.github.io/7842B-Journal/2019-10-16/statemachine/
#pragma once
#include "pros/rtos.hpp"
#include "pros/screen.hpp"

namespace lib {

// TODO: split this into a body file

template <typename State, State init_state = State::Idle>
class StateMachine {
 private:
  State state = init_state;
  pros::Mutex state_lock;

 public:
  StateMachine() {}

  virtual void loop() = 0;

  State get_state() {
    state_lock.take();
    State current_state = state;
    state_lock.give();
    return current_state;
  }

  void set_state(State new_state) {
    state_lock.take();
    state = new_state;
    state_lock.give();
  }
};

}  // namespace lib

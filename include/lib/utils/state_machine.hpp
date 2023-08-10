#pragma once
#include "pros/rtos.hpp"

namespace lib {

template <typename State, State init_state = State::Idle>
class StateMachine {
 private:
  State state = init_state;
  pros::Mutex state_lock;
  pros::Task* task{nullptr};

 public:
  StateMachine() {}

  void init() {
    if (task == nullptr) {
      task = new pros::Task([this] {
        while (true) {
          loop();
        }
      });
    }
  };

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

#include "lib/utils/state_machine.hpp"

#include "pros/rtos.hpp"

namespace lib {

template <class State>
State StateMachine<State>::get_state() {
  state_lock.take();
  return current_state;
  state_lock.give();
};

template <class State>
void StateMachine<State>::set_state(State new_state) {
  state_lock.take();
  current_state = new_state;
  state_lock.give();
};

template <class State>
void StateMachine<State>::start_loop() {
  if (task == nullptr) {
    task = new pros::Task{[this] {
      while (true) {
        loop();
      };
    }};
  }
}
}  // namespace lib

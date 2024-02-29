#include "lib/utils/task_wrapper.hpp"

namespace lib {

void TaskWrapper::start_task() {
  if (task == nullptr) {
    task = new pros::Task([this] {
      while (true) {
        this->loop();
        pros::delay(rate);
      }
    });
  }
}

void TaskWrapper::set_rate(int new_rate) { rate = new_rate; }

};  // namespace lib

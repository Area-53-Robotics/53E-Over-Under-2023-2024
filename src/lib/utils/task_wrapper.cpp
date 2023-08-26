#include "lib/utils/task-wrapper.hpp"

namespace lib {

void TaskWrapper::start_task() {
  if (task == nullptr) {
    task = new pros::Task([this] {
      while (true) {
        this->loop();
      }
    });
  }
}

};  // namespace lib

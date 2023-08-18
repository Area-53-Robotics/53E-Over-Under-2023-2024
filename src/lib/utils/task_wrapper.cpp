#include "lib/utils/task_wrapper.hpp"

namespace lib {

void TaskWrapper::loop() { throw "task loop isn't overridden!"; }

void TaskWrapper::start_task(const char* iname) {
  task = std::move(std::make_unique<pros::Task>(trampoline, this, iname));
}

void TaskWrapper::pause_task() { task->suspend(); }

void TaskWrapper::resume_task() { task->resume(); }

void TaskWrapper::stop_task() { task->remove(); }

char const* TaskWrapper::get_name() { return task->get_name(); }

void TaskWrapper::trampoline(void* iparam) {
  if (iparam) {
    TaskWrapper* that = static_cast<TaskWrapper*>(iparam);
    that->loop();
  }
}

}  // namespace lib

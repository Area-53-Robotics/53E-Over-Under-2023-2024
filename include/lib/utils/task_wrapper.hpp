// Credit to Ryan
// https://github.com/Ryan4253/RaidZeroLib/blob/bb9f94f087cae19f22a3d8048642b198f45b7fa1/include/RaidZeroLib/Utility/TaskWrapper.hpp#L1
// Inspired from:
// https://theol0403.github.io/7842B-Journal/2019-10-18/task-wrapper/

#pragma once
#include <memory>

#include "pros/rtos.hpp"

namespace lib {

class TaskWrapper {
 protected:
  TaskWrapper() = default;
  TaskWrapper(const TaskWrapper& itask) = delete;
  // TaskWrapper(TaskWrapper&& itask) = default;
  virtual ~TaskWrapper() = default;

  /**
   * Override this function to implement a custom task loop.
   * Will throw if not overridden.
   */
  virtual void loop();

 public:
  /**
   * Start the task.
   *
   * @param iname The task name, optional.
   */
  virtual void start_task(const char* iname = "TaskWrapper");

  virtual void resume_task();

  virtual void pause_task();

  /**
   * Kill the task.
   */
  virtual void stop_task();

  /**
   * Get the task name.
   *
   * @return The name.
   */
  virtual char const* get_name();

 private:
  static void trampoline(void* iparam);
  std::unique_ptr<pros::Task> task{nullptr};
};
}  // namespace lib

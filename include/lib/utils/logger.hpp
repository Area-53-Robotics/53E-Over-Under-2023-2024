#pragma once
#include <deque>
#include <string>
#include <vector>

#include "pros/rtos.hpp"
#include "state_machine.hpp"
#include "task_wrapper.hpp"

namespace lib {

/*
 * @brief This enum represents the different ways that messages are removed
 * from the internal buffer and then printed to stdout.
 */
enum class LoggerMode {
  Idle,
  FirstInLastOut,
  FirstInFirstOut,
  FirstInLastOutLossy,
  FirstInFirstOutLossy,
};

/*
 *  @brief This is an extremely simple logging implementation based on LemLib's.
 * Its meant to allow several tasks to print to stdout at once, and
 * assumes that it is the only task printing to stdout. If anything else prints
 * to stdout, ie printf, it could break the logger.
 */
class Logger : public StateMachine<LoggerMode>, public TaskWrapper {
 public:
  Logger();
  void log(std::string message);
  void telemetry(std::string message);

 private:
  // A deque is used here instead of a vector because we need to be able to push
  // and pop from both ends of the list, not just the beginning.
  std::deque<std::string> buffer;

  void loop() override;

  pros::Mutex lock;
};

}  // namespace lib

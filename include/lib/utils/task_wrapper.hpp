// Inspired from:
// https://theol0403.github.io/7842B-Journal/2019-10-18/task-wrapper/

#pragma once
#include <cstdio>
#include <memory>

#include "pros/rtos.hpp"

namespace lib {

class TaskWrapper {
 protected:
  virtual void loop() = 0;

 public:
  void start_task();
  void set_rate(int new_rate);

 private:
  int rate = 50;
  pros::Task *task{nullptr};
};

}  // namespace lib

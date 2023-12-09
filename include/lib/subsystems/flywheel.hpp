#pragma once

#include "api.h"
#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp"
#include "sylib/motor.hpp"
#include "sylib/sylib.hpp"

namespace lib {

enum class FlywheelState { Spinning, Idle };

class Flywheel : public StateMachine<FlywheelState>, public TaskWrapper {
 public:
  Flywheel(std::shared_ptr<sylib::Motor> i_motor, std::shared_ptr<sylib::Addrled> i_led);


  void toggle();

 private:
  void loop() override;
  std::shared_ptr<sylib::Motor> motor;
  std::shared_ptr<sylib::Addrled> led;
};
}  // namespace lib

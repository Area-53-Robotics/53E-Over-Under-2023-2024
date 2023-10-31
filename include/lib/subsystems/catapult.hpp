#pragma once
#include <memory>

#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class CatapultState { Idle, Loading, Ready, Firing, Repeating };

class Catapult : public lib::StateMachine<CatapultState>, public TaskWrapper {
 public:
  Catapult(std::shared_ptr<pros::Motor> i_motor,
           std::shared_ptr<pros::ADIDigitalIn> i_limit_switch);

  void fire();
  void toggle_repeating();
  void toggle_disabled();

 private:
  std::shared_ptr<pros::Motor> motor;
  std::shared_ptr<pros::ADIDigitalIn> limit_switch;

 protected:
  void loop() override;
};

}  // namespace lib

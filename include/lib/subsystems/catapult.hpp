#pragma once
#include <memory>

#include "lib/utils/state_machine.hpp"
#include "lib/utils/task_wrapper.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

namespace lib {

enum class CatapultState { Idle, Loading, Ready, Firing, Repeating };

class Catapult : public lib::StateMachine<CatapultState>, public TaskWrapper {
 public:
  Catapult(std::shared_ptr<pros::Motor> i_motor,
           std::shared_ptr<pros::Rotation> i_rotation_sensor);

  void fire();
  void toggle_repeating();
  void toggle_disabled();

 private:
  std::shared_ptr<pros::Motor> motor;
  std::shared_ptr<pros::Rotation> rotation_sensor;

 protected:
  void loop() override;
};

}  // namespace lib

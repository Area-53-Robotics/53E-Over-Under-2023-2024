#pragma once
#include <memory>

#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp"
#include "pros/motors.hpp"

namespace lib {

enum class CatapultState { Idle, Loading, Ready, Firing };

class Catapult : public lib::StateMachine<CatapultState>, public TaskWrapper {
 public:
  Catapult(std::shared_ptr<pros::Motor> i_motor);
  ~Catapult();

 private:
  std::shared_ptr<pros::Motor> motor;

 protected:
  void loop() override;
};

}  // namespace lib

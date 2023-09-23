#pragma once

#include "lib/utils/state_machine.hpp"
#include "lib/utils/task-wrapper.hpp" 
#include "api.h"

namespace lib {

enum class FlapState {Expanded, Idle};

class Flaps : public StateMachine<FlapState>, public TaskWrapper {
    public:
     Flaps(std::shared_ptr<pros::ADIAnalogOut> piston);
     
    private:

     std::shared_ptr<pros::ADIAnalogOut> piston;
     void loop() override;

};
}

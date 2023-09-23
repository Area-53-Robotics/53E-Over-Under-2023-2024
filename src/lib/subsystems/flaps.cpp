#include "lib/subsystems/flaps.hpp"
namespace lib{
    Flaps::Flaps(std::shared_ptr<pros::ADIAnalogOut> i_piston){
        piston = i_piston;
    };

    void Flaps::loop(){
        while(true){
            switch (get_state()) {
                case FlapState::Expanded: 
                    piston->set_value(true);
                    break; 
                case FlapState::Idle:
                    piston->set_value(false);                    

            }
         pros::delay(20);
        }
    }

}

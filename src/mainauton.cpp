#include "main.h"
#include "globals.hpp"
enum class AutonRoute {LeftRoute, RightRoute, LeftRouteWithGoal, RightRouteWithExtraGoal};
AutonRoute current_route = AutonRoute::LeftRoute;

void autonomous() { chassis.moveTo(0, 10, 2000); 
switch(current_route) {
    case AutonRoute::LeftRoute:
    chassis.moveTo(24, 12, 3000);
    intake.set_state(lib::IntakeState::Running); 
    chassis.turnTo(72, 12, 2000);
    intake.set_state(lib::IntakeState::Idle);
    chassis.moveTo(68, 12, 3000);
    //touch the bar with the wiggly antenna. 
    break;
    case AutonRoute::RightRoute:
    chassis.turnTo(132, 48, 2000);
    chassis.moveTo(132, 48, 3000);
    intake.set_state(lib::IntakeState::Running);
    break; 
    case AutonRoute::LeftRouteWithGoal:
    chassis.moveTo(24, 12, 3000);
    intake.set_state(lib::IntakeState::Running);
    chassis.turnTo(72, 12, 2000);
    intake.set_state(lib::IntakeState::Idle);
    chassis.turnTo(72, 48, 2000);
    chassis.moveTo(72, 48, 3000);
    intake.set_state(lib::IntakeState::Reversed);
    break;
    case AutonRoute::RightRouteWithExtraGoal:
    chassis.turnTo(132, 48, 2000);
    chassis.moveTo(132, 48, 3000);
    intake.set_state(lib::IntakeState::Reversed);
    chassis.moveTo(72, 48, 3000);
    intake.set_state(lib::IntakeState::Running);
    chassis.turnTo(120, 48, 2000);
    chassis.moveTo(120, 48, 3000);
    intake.set_state(lib::IntakeState::Reversed);
    break;
}
}



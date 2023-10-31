#include "lib/subsystems/catapult.hpp"

#include <cstdio>

#include "pros/rtos.hpp"
#include "pros/screen.hpp"

namespace lib {

Catapult::Catapult(std::shared_ptr<pros::Motor> i_motor,
                   std::shared_ptr<pros::ADIDigitalIn> i_limit_switch)
    : motor(i_motor), limit_switch(i_limit_switch) {
  motor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  set_state(CatapultState::Loading);
};

void Catapult::fire() {
  if (get_state() == CatapultState::Ready) {
    printf("firing\n");
    set_state(CatapultState::Firing);
  }
}

void Catapult::toggle_repeating() {
  if (!(get_state() == CatapultState::Repeating)) {
    set_state(CatapultState::Repeating);
  } else {
    set_state(CatapultState::Loading);
  }
}

void Catapult::toggle_disabled() {
  if (!(get_state() == CatapultState::Idle)) {
    set_state(CatapultState::Idle);
  } else {
    set_state(CatapultState::Loading);
  }
}

void Catapult::loop() {
  switch (get_state()) {
    case CatapultState::Idle: {
      // This mode is meant to to completely disable the catapult
      motor->move(0);
      break;
    }

    case CatapultState::Loading: {
      if (limit_switch->get_value()) {
        set_state(CatapultState::Ready);
      }

      motor->move(127);
      break;
    }

    case CatapultState::Ready: {
      if (!limit_switch->get_value()) {
        set_state(CatapultState::Loading);
      }

      motor->move(0);
      break;
    }

    case CatapultState::Firing: {
      printf("Firing\n");
      while (limit_switch->get_value()) {
        motor->move(127);
      }
      set_state(CatapultState::Loading);
      break;
    }

    case CatapultState::Repeating: {
      motor->move(127);
      break;
    }
  }
  pros::delay(20);
};
}  // namespace lib

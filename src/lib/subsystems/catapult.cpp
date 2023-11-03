#include "lib/subsystems/catapult.hpp"

#include <cstdio>

#include "pros/rtos.hpp"
#include "pros/screen.hpp"

namespace lib {

// We define a range of angles that the catapult is considered loaded for
// The rotation sensor outputs in centidegrees
const float MIN_LOADED_ANGLE = 32000;
const float MAX_LOADED_ANGLE = 30000;

Catapult::Catapult(std::shared_ptr<pros::Motor> i_motor,
                   std::shared_ptr<pros::Rotation> i_rotation_sensor)
    : motor(i_motor), rotation_sensor(i_rotation_sensor) {
  motor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  set_state(CatapultState::Loading);
};

bool is_cata_ready(float cataPosition) {
  if (cataPosition > MIN_LOADED_ANGLE or cataPosition < MAX_LOADED_ANGLE) {
    return false;
  } else {
    return true;
  }
}

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
      // This mode is meant to to completely disable the catapult, the state
      // machine cannot automatically escape from this mode.
      motor->move(0);
      break;
    }

    case CatapultState::Loading: {
      printf("loading\n");
      if (is_cata_ready(rotation_sensor->get_angle())) {
        set_state(CatapultState::Ready);
      }

      motor->move(127);
      break;
    }

    case CatapultState::Ready: {
      printf("ready\n");
      if (!is_cata_ready(rotation_sensor->get_angle())) {
        set_state(CatapultState::Loading);
      }

      motor->brake();
      break;
    }

    case CatapultState::Firing: {
      printf("Firing\n");
      while (rotation_sensor->get_angle() < MAX_LOADED_ANGLE) {
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

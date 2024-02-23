#pragma once

#include <string>

// selector configuration
#define HUE 120  // color of theme from 0-360
#define DEFAULT 0
#define AUTONS "Offensive", "Defensive", "Nothing"

namespace lib {
namespace selector {

extern int auton;
inline const char *b[] = {AUTONS, ""};

void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}  // namespace selector
}  // namespace lib

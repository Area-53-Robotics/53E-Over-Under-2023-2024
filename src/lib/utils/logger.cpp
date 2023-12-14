#include "lib/utils/logger.hpp"

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

#include "fmt/core.h"

namespace lib {
using std::string;

Logger::Logger(){};

void Logger::log(std::string message) {
  // lock.take();
  buffer.push_front(message);
  // lock.give();
};

void Logger::telemetry(std::string message) {
  // lock.take();
  message = fmt::format("TEL_STRT{}TEL_END", message);
  buffer.push_front(message);
  // lock.give();
};

void Logger::loop() {
  if (buffer.size() == 0) {
    return;
  }

  switch (get_state()) {
    case LoggerMode::Idle:
      break;
    case LoggerMode::FirstInLastOut: {
      std::string message = buffer.back();
      std::cout << message << std::endl;
      buffer.pop_back();
      break;

      break;
    }
    case LoggerMode::FirstInFirstOut: {
      std::string message = buffer.front();
      std::cout << message << std::endl;
      buffer.pop_front();
      break;
    }
    case LoggerMode::FirstInLastOutLossy:
      break;
    case LoggerMode::FirstInFirstOutLossy:
      break;
  };
}

}  // namespace lib

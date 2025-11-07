#include "Utils.hpp"

#include <iostream>

void Common::Utils::joinThread(std::thread &thread) {
  if (thread.joinable()) {
    thread.join();
  }
}

#pragma once

#include <chrono>
#include <mutex>

class Timer {
public:
  static void init();
  static int time();
  static void sleep(int t);

private:
  static inline std::chrono::high_resolution_clock::time_point start_;
};

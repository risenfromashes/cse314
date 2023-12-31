#include <bits/chrono.h>
#include <chrono>
#include <complex>
#include <thread>

#include "random.h"
#include "timer.h"

using namespace std::chrono;
using namespace std::literals::chrono_literals;

void Timer::init() { start_ = high_resolution_clock::now(); }

int Timer::time() {
  auto elapsed = high_resolution_clock::now() - start_;
  return duration_cast<seconds>(elapsed).count();
}

void Timer::sleep(int t) { std::this_thread::sleep_for(t * 1s); }

void Timer::rand_delay() { std::this_thread::sleep_for(Random::get() * 1s); }

#include "random.h"
#include <cstdint>
#include <iostream>
#include <random>

void Random::init() {
  std::random_device rand;
  rng_.seed(rand());
}

uint32_t Random::get() {
  std::scoped_lock lck(mtx_);
  int ret = dist_(rng_);
  return ret + 1;
}

#include "random.h"
#include <cstdint>
#include <random>

void Random::init() {
  std::random_device rand;
  rng_.seed(rand());
}

uint32_t Random::get() {
  std::scoped_lock lck(mtx_);
  return dist_(rng_);
}

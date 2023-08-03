#pragma once

#include <cstdint>
#include <mutex>
#include <random>

class Random {
public:
  static void init();
  static uint32_t get();

private:
  static inline std::mutex mtx_;
  static inline std::mt19937 rng_;
  static inline std::poisson_distribution<uint32_t> dist_;
};

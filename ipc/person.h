#pragma once

#include <concepts>
#include <memory>
#include <semaphore>
#include <thread>
#include <vector>

class Person {
public:
  int id() { return id_; }
  std::string_view name() { return name_; }

  void wait();
  void notify();

protected:
  Person(std::string designation, int id);

protected:
  std::string name_;
  int id_;
  std::thread thread_;

  std::binary_semaphore sem_{0};

  template <std::derived_from<Person> T>
  friend void join(std::vector<std::shared_ptr<T>> &g);
};

template <std::derived_from<Person> T>
void join(std::vector<std::shared_ptr<T>> &g) {
  for (auto &s : g) {
    if (s->thread_.joinable()) {
      s->thread_.join();
    }
  }
}

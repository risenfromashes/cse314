#pragma once

#include <semaphore>
#include <thread>

class Person {
public:
  void start();

  int id() { return id_; }

  void wait();
  void notify();

protected:
  Person(std::string designation, int id);
  virtual void action() = 0;

private:
  std::string name_;
  int id_;
  std::jthread thread_;

  std::binary_semaphore sem_{0};
};

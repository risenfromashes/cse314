#pragma once

#include <compare>
#include <memory>
#include <semaphore>
#include <thread>

#include "person.h"

class Group;

class Student : public Person {
public:
  Student(int id);
  int group_id();

  void recv_print();
  void submit_print();

private:
  void action() override;

  std::weak_ptr<Group> group_;

  std::binary_semaphore print_sem_;
};
#pragma once

#include <memory>
#include <shared_mutex>

#include "staff.h"
#include "student.h"

class EntryBook {
public:
  void read(Staff *staff);
  void write(Student *student);

  int submission_count() { return submission_count_; }

private:
  std::shared_mutex mtx_;

  int submission_count_ = 0;
};

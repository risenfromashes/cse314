#pragma once

#include <vector>

#include "student.h"

class Group {
public:
  void set_leader(std::shared_ptr<Student> leader);
  std::shared_ptr<Student> leader();

  void add_member(std::shared_ptr<Student> s);

  void prepare_binding();

private:
  std::shared_ptr<Student> leader_;
  std::vector<std::shared_ptr<Student>> members_;
};

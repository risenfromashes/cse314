#pragma once

#include <memory>
#include <vector>

#include "student.h"

class Group : public std::enable_shared_from_this<Group> {
public:
  Group(int id);

  void set_leader(std::shared_ptr<Student> leader);
  std::shared_ptr<Student> leader();

  void add_member(std::shared_ptr<Student> s);

  void prepare_binding();

  int id() { return id_; }

private:
  std::shared_ptr<Student> leader_;
  std::vector<std::shared_ptr<Student>> members_;
  int id_;
};

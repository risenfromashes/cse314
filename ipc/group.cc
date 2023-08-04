#include "group.h"
#include <cassert>

Group::Group(int id) : id_(id) {}

void Group::set_leader(std::shared_ptr<Student> leader) { leader_ = leader; }

std::shared_ptr<Student> Group::leader() { return leader_; }

void Group::add_member(std::shared_ptr<Student> student) {
  student->set_group(shared_from_this());
  members_.push_back(student);
}

void Group::prepare_binding() {
  for (auto &s : members_) {
    s->recv_print();
  }
}

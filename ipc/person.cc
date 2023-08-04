#include "person.h"

Person::Person(std::string des, int id) : id_(id) {
  name_ = std::move(des);
  name_ += ' ';
  name_ += std::to_string(id);
}

void Person::wait() { sem_.acquire(); }

void Person::notify() { sem_.release(); }

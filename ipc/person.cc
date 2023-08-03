#include "person.h"

void Person::start() {
  thread_ = std::jthread([this] { action(); });
}

Person::Person(std::string des, int id) {
  name_ = std::move(des);
  name_ += ' ';
  name_ += std::to_string(id);
}

void Person::wait() { sem_.acquire(); }

void Person::notify() { sem_.release(); }

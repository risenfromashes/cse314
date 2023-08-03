
#include "printing_station.h"
#include "config.h"
#include <cassert>
#include <chrono>
#include <mutex>
#include <thread>

PrintingStation::PrintingStation() {}

void PrintingStation::acquire(std::shared_ptr<Student> student) {
  {
    std::scoped_lock lock(mtx_);
    if (!busy_) {
      busy_ = true;
    } else {
      waiting_.insert(student);
    }
  }
  /* wait for text from peer */
  student->wait();
}

void PrintingStation::release(std::shared_ptr<Student> student) {
  std::scoped_lock lock(mtx_);
  assert(busy_);
  busy_ = false;

  for (auto s : waiting_) {
    if (s->group_id() == student->group_id()) {
      if (test(s)) {
        break;
      }
    }
  }

  if (!busy_) {
    for (auto s : waiting_) {
      if (s->group_id() != student->group_id()) {
        if (test(s)) {
          break;
        }
      }
    }
  }
}

bool PrintingStation::test(std::shared_ptr<Student> student) {
  if (!busy_) {
    busy_ = true;
    waiting_.erase(student);
    student->notify();
    return true;
  }
  return false;
}

void PrintingStation::use(std::shared_ptr<Student> student) {
  std::this_thread::sleep_for(std::chrono::seconds(Config::w()));
}

void PrintingStation::take(std::shared_ptr<Student> student) {
  acquire(student);
  use(student);
  release(student);
}

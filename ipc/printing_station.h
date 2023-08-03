#pragma once
#include <memory>
#include <mutex>
#include <semaphore>
#include <set>

#include "student.h"

class PrintingStation {
public:
  PrintingStation();
  void take(std::shared_ptr<Student> student);

private:
  void acquire(std::shared_ptr<Student> student);
  void release(std::shared_ptr<Student> student);
  void use(std::shared_ptr<Student> student);
  bool test(std::shared_ptr<Student> student);

  /* lock must be held on mtx_ while accessing these */
  bool busy_;
  std::set<std::shared_ptr<Student>> waiting_;

  std::mutex mtx_;
};

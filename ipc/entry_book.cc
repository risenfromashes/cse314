#include "entry_book.h"
#include "config.h"
#include "timer.h"
#include <thread>

void EntryBook::read(Staff *staff) {
  std::shared_lock lck(mtx_);
  Timer::sleep(Config::y());
}

void EntryBook::write(Student *student) {
  std::unique_lock lck(mtx_);
  Timer::sleep(Config::y());
  submission_count_++;
}

#include "entry_book.h"
#include "config.h"
#include "group.h"
#include "timer.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <syncstream>
#include <thread>

void EntryBook::read(Staff *staff) {
  std::shared_lock lck(mtx_);
  std::osyncstream(std::cout)
      << staff->name() << " has started reading the entry book at time "
      << Timer::time() << ". No of submission = " << submission_count_
      << std::endl;
  Timer::sleep(Config::y());
}

void EntryBook::write(Student *leader) {
  auto g = leader->group();

  assert(leader->is_leader());
  assert(g);

  std::unique_lock lck(mtx_);
  Timer::sleep(Config::y());

  std::osyncstream(std::cout)
      << "Group " << g->id() << " has submitted the report at time "
      << Timer::time() << std::endl;

  submission_count_++;
}

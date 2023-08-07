#include "staff.h"
#include "config.h"
#include "entry_book.h"
#include "random.h"

#include <chrono>
#include <iostream>

Staff::Staff(int id) : Person("Staff", id) {}

void Staff::action() {
  int m = Config::m();
  while (entry_book_->submission_count() < m) {
    entry_book_->read(this);
    /* to not starve writers */
    std::this_thread::sleep_for(
        std::chrono::milliseconds(Random::get() % 5 + 1));
  }
}

void Staff::start() {
  auto self = shared_from_this();
  thread_ = std::thread([self] { self->action(); });
}

void Staff::set_entry_book(std::shared_ptr<EntryBook> eb) { entry_book_ = eb; }

std::shared_ptr<EntryBook> Staff::entry_book() { return entry_book_; }

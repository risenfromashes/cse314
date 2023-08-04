#pragma once

#include <memory>

#include "person.h"

class EntryBook;

class Staff : public Person, public std::enable_shared_from_this<Staff> {
public:
  Staff(int id);

  void set_entry_book(std::shared_ptr<EntryBook> eb);
  std::shared_ptr<EntryBook> entry_book();

  void start();

private:
  void action();

  std::shared_ptr<EntryBook> entry_book_;
};
#pragma once

#include <memory>

#include "person.h"

class EntryBook;

class Staff : public Person {
public:
  Staff(int id);

private:
  void action() override;

  std::shared_ptr<EntryBook> entry_book_;
};
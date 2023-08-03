#include "staff.h"
#include "entry_book.h"

Staff::Staff(int id) : Person("Staff", id) {}

void Staff::action() {
  for (;;) {
    entry_book_->read(this);
  }
}

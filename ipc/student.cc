#include "student.h"
#include "group.h"
#include "printing_station.h"
#include "timer.h"

#include <iostream>

#include "binding_stations.h"
#include "entry_book.h"

Student::Student(int id) : Person("Student", id), print_sem_(0) {}

void Student::recv_print() { print_sem_.acquire(); }

void Student::submit_print() { print_sem_.release(); }

void Student::set_printing_station(std::shared_ptr<PrintingStation> ps) {
  print_station_ = ps;
}

void Student::set_group(std::shared_ptr<Group> g) { group_ = g; }

void Student::set_binding_stations(std::shared_ptr<BindingStations> bs) {
  binding_stations_ = bs;
}

void Student::set_entry_book(std::shared_ptr<EntryBook> eb) {
  entry_book_ = eb;
}

std::shared_ptr<PrintingStation> Student::printing_station() {
  return print_station_;
}

std::shared_ptr<Group> Student::group() { return group_.lock(); }

std::shared_ptr<BindingStations> Student::binding_station() {
  return binding_stations_;
}

std::shared_ptr<EntryBook> Student::entry_book() { return entry_book_; }

int Student::group_id() {
  if (auto g = group()) {
    return g->id();
  }
  return 0;
}

bool Student::is_leader() {
  if (auto g = group()) {
    return g->leader().get() == this;
  }
  return false;
}

void Student::start() {
  auto self = shared_from_this();
  thread_ = std::thread([self] { self->action(); });
}

void Student::action() {
  Timer::rand_delay();
  print_station_->take(shared_from_this());
  submit_print();
  if (is_leader()) {
    if (auto g = group()) {
      g->prepare_binding();
      binding_stations_->bind(this);
      entry_book_->write(this);
    }
  }
}

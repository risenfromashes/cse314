#pragma once

#include <compare>
#include <memory>
#include <semaphore>
#include <thread>

#include "person.h"

class Group;
class PrintingStation;
class BindingStations;
class EntryBook;

class Student : public Person, public std::enable_shared_from_this<Student> {
public:
  Student(int id);

  void set_group(std::shared_ptr<Group> g);
  void set_printing_station(std::shared_ptr<PrintingStation> ps);
  void set_binding_stations(std::shared_ptr<BindingStations> bs);
  void set_entry_book(std::shared_ptr<EntryBook> eb);

  std::shared_ptr<PrintingStation> printing_station();
  std::shared_ptr<Group> group();
  std::shared_ptr<BindingStations> binding_station();
  std::shared_ptr<EntryBook> entry_book();

  int group_id();

  void recv_print();
  void submit_print();

  bool is_leader();

  void start();

private:
  void action();

  std::weak_ptr<Group> group_;

  std::shared_ptr<PrintingStation> print_station_;
  std::shared_ptr<BindingStations> binding_stations_;
  std::shared_ptr<EntryBook> entry_book_;

  std::binary_semaphore print_sem_;
};
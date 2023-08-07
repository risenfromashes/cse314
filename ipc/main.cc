#include "binding_stations.h"
#include "config.h"
#include "entry_book.h"
#include "group.h"
#include "printing_station.h"
#include "random.h"
#include "staff.h"
#include "student.h"
#include "timer.h"

#include <cassert>
#include <cstdio>
#include <iostream>

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (i < argc - 1) {
      if (std::string_view(argv[i]) == "-i") {
        std::freopen(argv[i + 1], "r", stdin);
      }
      if (std::string_view(argv[i]) == "-o") {
        std::freopen(argv[i + 1], "w", stdout);
      }
    }
  }

  int n, m;
  int w, x, y;

  Random::init();
  Timer::init();

  std::cin >> n >> m;
  std::cin >> w >> x >> y;

  Config::set_w(w);
  Config::set_x(x);
  Config::set_y(y);

  std::vector<std::shared_ptr<Student>> students(n);
  std::vector<std::shared_ptr<Group>> groups(n / m);

  std::vector<std::shared_ptr<Staff>> staffs(2);

  std::vector<std::shared_ptr<PrintingStation>> printing_stations(4);
  std::shared_ptr<BindingStations> binding_stations =
      std::make_shared<BindingStations>(2);
  std::shared_ptr<EntryBook> entry_book = std::make_shared<EntryBook>();

  for (int i = 0; i < 4; i++) {
    printing_stations[i] = std::make_shared<PrintingStation>();
  }

  for (int i = 1; i <= n; i++) {
    students[i - 1] = std::make_shared<Student>(i);
    students[i - 1]->set_printing_station(printing_stations[i % 4]);
    students[i - 1]->set_binding_stations(binding_stations);
    students[i - 1]->set_entry_book(entry_book);
  }

  for (int gid = 1; gid <= (n / m); gid++) {
    // create group and set leader
    groups[gid - 1] = std::make_shared<Group>(gid);
    groups[gid - 1]->set_leader(students[gid * m - 1]);
    // add members
    for (int sid = (gid - 1) * m + 1; sid <= gid * m; sid++) {
      groups[gid - 1]->add_member(students[sid - 1]);
    }
    assert(students[gid * m - 1]->is_leader());
  }

  for (int i = 1; i <= n; i++) {
    students[i - 1]->start();
  }

  for (int i = 1; i <= 2; i++) {
    staffs[i - 1] = std::make_shared<Staff>(i);
    staffs[i - 1]->set_entry_book(entry_book);
    staffs[i - 1]->start();
  }

  join(students);
  join(staffs);

  return 0;
}

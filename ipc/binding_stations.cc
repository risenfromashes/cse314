#include "binding_stations.h"
#include "config.h"
#include "group.h"
#include "timer.h"
#include <cassert>
#include <iostream>
#include <syncstream>
#include <thread>

BindingStations::BindingStations(int n) : n_stations_(n), sem_(n) {}

void BindingStations::bind(Student *leader) {
  auto g = leader->group();

  assert(leader->is_leader());
  assert(g);

  sem_.acquire();
  std::osyncstream(std::cout)
      << "Group " << g->id() << " has started binding at time " << Timer::time()
      << std::endl;
  Timer::sleep(Config::x());
  std::osyncstream(std::cout)
      << "Group " << g->id() << " has finished binding at time "
      << Timer::time() << std::endl;
  Timer::sleep(Config::x());
  sem_.release();
}
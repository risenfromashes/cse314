#include "binding_stations.h"
#include "config.h"
#include "timer.h"
#include <thread>

BindingStations::BindingStations(int n) : n_stations_(n), sem_(n) {}

void BindingStations::bind(Student *student) {
  sem_.acquire();
  Timer::sleep(Config::x());
  sem_.release();
}
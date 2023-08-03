#pragma once

#include "student.h"
#include <semaphore>

class BindingStations {
public:
  BindingStations(int n);
  void bind(Student *student);

private:
  /* maximum of 16 */
  int n_stations_;
  std::counting_semaphore<16> sem_;
};

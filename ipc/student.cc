#include "student.h"

Student::Student(int id) : Person("Student", id), print_sem_(0) {}

void Student::recv_print() { print_sem_.acquire(); }

void Student::submit_print() { print_sem_.release(); }
#include "config.h"

void Config::set_w(int w) { w_ = w; }
void Config::set_y(int y) { y_ = y; }
void Config::set_x(int x) { x_ = x; }
void Config::set_group_count(int m) { group_count_ = m; }

int Config::w() { return w_; }
int Config::y() { return y_; }
int Config::x() { return x_; }
int Config::group_count() { return group_count_; }

#include "config.h"

void Config::set_w(int w) { w_ = w; }
void Config::set_y(int y) { y_ = y; }
void Config::set_x(int x) { x_ = x; }

int Config::w() { return w_; }
int Config::y() { return y_; }
int Config::x() { return x_; }

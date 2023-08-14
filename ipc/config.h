#pragma once

class Config {
public:
  static void set_w(int w);
  static void set_y(int y);
  static void set_x(int x);
  static void set_group_count(int m);

  static int w();
  static int y();
  static int x();
  static int group_count();

private:
  inline static int w_ = 1;
  inline static int x_ = 1;
  inline static int y_ = 1;
  inline static int group_count_ = 1;
};

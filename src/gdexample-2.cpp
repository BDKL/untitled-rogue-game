#include "gdexample-2.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample_2::_bind_methods() {}

GDExample_2::GDExample_2() {
  // Initialize any variables here.
  time_passed = 0.0;
}

GDExample_2::~GDExample_2() {
  // Add your cleanup here.
}

void GDExample_2::_process(double delta) {
  time_passed += delta;

  Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 1.0)),
                                 10.0 + (10.0 * cos(time_passed * 1.5)));

  set_position(new_position);
}

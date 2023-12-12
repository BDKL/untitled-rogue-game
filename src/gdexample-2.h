#ifndef GDEXAMPLE_2_H
#define GDEXAMPLE_2_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class GDExample_2 : public Sprite2D {
  GDCLASS(GDExample_2, Sprite2D)

private:
  double time_passed;

protected:
  static void _bind_methods();

public:
  GDExample_2();
  ~GDExample_2();

  void _process(double delta);
};

} // namespace godot

#endif

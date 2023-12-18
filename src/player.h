#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_object2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class Player : public Node2D {
  GDCLASS(Player, Node2D);

private:
  Vector2 velocity;
  double speed;

protected:
  static void _bind_methods();

public:
  Player();
  ~Player();
  void _process(double delta);
  void set_speed(const double speed);
  double get_speed() const;
};

#endif // PLAYER_H

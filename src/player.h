#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_object2d.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

class Player : public CharacterBody2D {
  GDCLASS(Player, CharacterBody2D);

private:
  Vector2 velocity;
  Vector2 screen_size;
  real_t y_position;
  real_t x_position;
  Vector2 overall_pos;
  double speed;
  int health, buff, debuff;
  bool animation_flag;
  AnimatedSprite2D *sprite_handler;
  SpriteFrames *frames;
  ResourceLoader rsrc_loader;

protected:
  static void _bind_methods();

public:
  Player();
  ~Player();
  void _process(double delta);
  void set_speed(const double speed);
  double get_speed() const;
  int get_health();
  void update_health(int buff, int debuff);
};

#endif // PLAYER_H

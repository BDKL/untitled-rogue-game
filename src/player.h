#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_object2d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

class Player : public Area2D {
  GDCLASS(Player, Area2D);

private:
    float x_coord=0;
    float y_coord=0;

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void check_movement();
    void move_up();
    void move_left();
    void move_down();
    void move_right();

};

#endif // PLAYER_H

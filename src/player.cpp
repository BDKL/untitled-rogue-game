#include "player.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Player::Player() {
  //    I don't know what to add here
  if (Engine::get_singleton()->is_editor_hint()) {
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
  }
  UtilityFunctions::print("player started");
}

Player::~Player() {
  // clean up
}

void Player::_process(double delta) {
  velocity = Vector2(0.0f, 0.0f);
  Input &input_singleton = *Input::get_singleton();

  if (input_singleton.is_action_pressed("d")) {
    velocity.x += 1.0f;
    UtilityFunctions::print("d pressionado");
    UtilityFunctions::print(get_position());
  }
  if (input_singleton.is_action_pressed("a")) {
    velocity.x -= 1.0f;
    UtilityFunctions::print("a pressionado");
    UtilityFunctions::print(get_position());
  }
  if (input_singleton.is_action_pressed("w")) {
    velocity.y -= 1.0f;
    UtilityFunctions::print("w pressionado");
    UtilityFunctions::print(get_position());
  }
  if (input_singleton.is_action_pressed("s")) {
    velocity.y += 1.0f;
    UtilityFunctions::print("s pressionado");
    UtilityFunctions::print(get_position());
  }

  set_position(get_position() + (velocity * speed * delta));
}

void Player::set_speed(const double speed) { this->speed = speed; }

double Player::get_speed() const { return speed; }

void Player::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
  ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
  ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "speed"),
                        "set_speed", "get_speed");
}

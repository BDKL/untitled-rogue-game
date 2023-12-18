#include "player.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Player::Player() {
  if (Engine::get_singleton()->is_editor_hint()) {
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
  }
  UtilityFunctions::print("player started");
  // screen_size = get_viewport_rect().size;
  health = 10;
  buff = 0;
  debuff = 0;
}

Player::~Player() {
  // clean up
}

void Player::_process(double delta) {
  velocity = Vector2(0.0f, 0.0f);
  // x_position = get_position().x;
  // y_position = get_position().y;
  // overall_pos = get_position();
  Input &input_singleton = *Input::get_singleton();

  if (input_singleton.is_action_pressed("d")) {
    velocity.x += 1.0f;
    if (input_singleton.is_action_pressed("shift"))
      velocity.x += 10.0f;
  }

  if (input_singleton.is_action_pressed("a")) {
    velocity.x -= 1.0f;
    if (input_singleton.is_action_pressed("shift"))
      velocity.x -= 10.0f;
  }

  if (input_singleton.is_action_pressed("w")) {
    velocity.y -= 1.0f;
    if (input_singleton.is_action_pressed("shift"))
      velocity.y -= 10.0f;
  }

  if (input_singleton.is_action_pressed("s")) {
    velocity.y += 1.0f;
    if (input_singleton.is_action_pressed("shift"))
      velocity.y += 10.0f;
  }
  set_position(get_position() + (velocity * speed * delta));

  // some idea for health management/gameplay
  // +1 health buff on LMB1 and -1 health debuff on RMB1
  if (input_singleton.is_action_pressed("LMB1")) {
    buff += 1;
  }

  if (input_singleton.is_action_pressed("RMB1")) {
    debuff -= 1;
  }

  if (buff != 0 or debuff != 0) {
    update_health(buff, debuff);
    buff = 0;
    debuff = 0;
  }

  /*
  TODO:
    add here the logic so the player can't go beyond the screen size (there is a
    function for this called Math::clamp glhf)
  */
}

void Player::set_speed(const double speed) { this->speed = speed; }

double Player::get_speed() const { return speed; }

int Player::get_health() { return this->health; }

void Player::update_health(int buff, int debuff) {
  if (buff != 0) {
    this->health += buff;
    UtilityFunctions::print("current health after buff: ");
    UtilityFunctions::print(this->health);
  }

  if (debuff != 0) {
    this->health += debuff;
    UtilityFunctions::print("current health after debuff: ");
    UtilityFunctions::print(this->health);
  }
}

void Player::_bind_methods() {
  ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
  ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
  ClassDB::bind_method(D_METHOD("get_health"), &Player::get_health);
  ClassDB::bind_method(D_METHOD("update_health", "buff", "debuff"),
                       &Player::update_health);
  ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "speed"),
                        "set_speed", "get_speed");
}

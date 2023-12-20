#include "player.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Player::Player() {
  // this is prevents the code from running while in editing mode
  if (Engine::get_singleton()->is_editor_hint())
    set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);

  UtilityFunctions::print("player started");
  // screen_size = get_viewport_rect().size;
  health = 10;
  buff = 0;
  debuff = 0;
  animation_flag = false;

  // objects declarations
  sprite_handler = memnew(AnimatedSprite2D);
  frames = memnew(SpriteFrames);

  // add AnimatedSprite2D as child
  Player::add_child(sprite_handler);

  // add new animation and remove default
  frames->add_animation("fazuelen");
  frames->remove_animation("default");

  // load and add frames
  frames->add_frame("fazuelen", rsrc_loader.load("res://L1.png", ""), 1, 0);
  frames->add_frame("fazuelen", rsrc_loader.load("res://L2.png", ""), 1, 1);

  // start animation loop
  frames->set_animation_loop("fazuelen", true);
  sprite_handler->set_sprite_frames(frames);
}

Player::~Player() {
  // clean up
  memdelete(sprite_handler);
  memdelete(frames);
}

void Player::_process(double delta) {
  velocity = Vector2(0.0f, 0.0f);
  Input &input_singleton = *Input::get_singleton();
  // x_position = get_position().x;
  // y_position = get_position().y;
  // overall_pos = get_position();

  if (animation_flag == true) {

    sprite_handler->play("fazuelen", 1, false);

    UtilityFunctions::print("animation true");
    UtilityFunctions::print(frames->get_animation_names());
  }

  if (input_singleton.is_action_pressed("d")) {
    velocity.x += 1.0f;
    animation_flag = true;
    if (input_singleton.is_action_pressed("shift"))
      velocity.x += 10.0f;
  }

  if (input_singleton.is_action_pressed("a")) {
    velocity.x -= 1.0f;
    animation_flag = true;
    if (input_singleton.is_action_pressed("shift"))
      velocity.x -= 10.0f;
  }

  if (input_singleton.is_action_pressed("w")) {
    velocity.y -= 1.0f;
    animation_flag = true;
    if (input_singleton.is_action_pressed("shift"))
      velocity.y -= 10.0f;
  }

  if (input_singleton.is_action_pressed("s")) {
    velocity.y += 1.0f;
    animation_flag = true;
    if (input_singleton.is_action_pressed("shift"))
      velocity.y += 10.0f;
  }
  // updating position
  set_position(get_position() + (velocity * speed * delta));

  // some idea for health management/gameplay
  // +1 health buff on LMB1 and -1 health debuff on RMB1
  if (input_singleton.is_action_pressed("LMB1"))
    buff += 1;

  if (input_singleton.is_action_pressed("RMB1"))
    debuff -= 1;

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

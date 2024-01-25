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
  walking_animation_flag = false;
  base_speed = 1.0f;
  speedMult = 1.0f;

  // objects declarations
  sprite_handler = memnew(AnimatedSprite2D);
  frames = memnew(SpriteFrames);

  // add AnimatedSprite2D as child
  Player::add_child(sprite_handler);

  // add new animation and remove default
  frames->add_animation("attacking");
  frames->add_animation("walking");
  frames->add_animation("resting");
  frames->remove_animation("default");

  // load and add frames to walking animation
  frames->add_frame("walking",
                    rsrc_loader.load("res://assets/Jacare andandinho1.png", ""),
                    1, 0);
  frames->add_frame("walking",
                    rsrc_loader.load("res://assets/Jacare andandinho2.png", ""),
                    1, 1);
  frames->add_frame("walking",
                    rsrc_loader.load("res://assets/Jacare andandinho3.png", ""),
                    1, 2);
  frames->add_frame("walking",
                    rsrc_loader.load("res://assets/Jacare andandinho4.png", ""),
                    1, 3);

  // load and add frames to resting animation
  frames->add_frame("resting",
                    rsrc_loader.load("res://assets/Jacare andandinho1.png", ""),
                    1, 0);

  // load and add frames to attacking animation
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F1.png", ""), 1,
                    0);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F2.png", ""), 1,
                    1);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F3.png", ""), 1,
                    2);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F4.png", ""), 1,
                    3);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F5.png", ""), 1,
                    4);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F6.png", ""), 1,
                    5);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F7.png", ""), 1,
                    6);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F8.png", ""), 1,
                    7);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F9.png", ""), 1,
                    8);
  frames->add_frame("attacking", rsrc_loader.load("res://assets/F10.png", ""),
                    1, 9);

  // start animation loop
  frames->set_animation_loop("walking", true);

  sprite_handler->set_sprite_frames(frames);
}

Player::~Player() {
  // clean up
  // memdelete(sprite_handler);
  // memdelete(frames);
}

void Player::_process(double delta) {
  velocity = Vector2(0.0f, 0.0f);
  Input &input_singleton = *Input::get_singleton();
  // x_position = get_position().x;
  // y_position = get_position().y;
  // overall_pos = get_position();
  if (input_singleton.is_action_pressed("shift")) {
    speedMult = 10.0f;
  } else {
    speedMult = 1.0f;
  }

  // sprite_handler->play("resting", 1, false);

  // if (walking_animation_flag == true) {
  //   sprite_handler->play("walking", 1, false);
  //   walking_animation_flag = false;

  //   // UtilityFunctions::print("animation true");
  //   // UtilityFunctions::print(frames->get_animation_names());
  // } else {
  //   sprite_handler->play("resting", 1, false);
  // }

  if (input_singleton.is_action_pressed("d")) {
    velocity.x += base_speed * speedMult;
    sprite_handler->play("walking", 1, false);
    // walking_animation_flag = true;
  }

  if (input_singleton.is_action_pressed("a")) {
    velocity.x -= base_speed * speedMult;
    sprite_handler->play("walking", 1, false);
    // walking_animation_flag = true;
  }

  if (input_singleton.is_action_pressed("w")) {
    velocity.y -= base_speed * speedMult;
    sprite_handler->play("walking", 1, false);
    // walking_animation_flag = true;
  }

  if (input_singleton.is_action_pressed("s")) {
    velocity.y += base_speed * speedMult;
    sprite_handler->play("walking", 1, false);
    // walking_animation_flag = true;
  }

  // updating position
  set_position(get_position() + (velocity * speed * delta));

  // attack handling
  if (input_singleton.is_action_pressed("J")) {
    sprite_handler->play("attacking", 4, false);
  }

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

  if (!input_singleton.is_anything_pressed())
    sprite_handler->play("resting", 1, false);

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

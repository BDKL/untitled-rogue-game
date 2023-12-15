#include "player.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

 Player::Player() {
//    I don't know what to add here
     UtilityFunctions::print("player started");

}

Player::~Player(){
// clean up
}

void Player::move_up() {
    x_coord+=1;
    UtilityFunctions::print("up");
}

void Player::move_left() {
    x_coord-=1;
    UtilityFunctions::print("left");
}

void Player::move_down() {
    x_coord-=1;
    UtilityFunctions::print("down");
}

void Player::move_right() {
    y_coord+=1;
    UtilityFunctions::print("right");
}

void Player::check_movement() {
    Input *input = Input::get_singleton();

    if (input->is_key_pressed(KEY_W)) {
        move_up();
    }

    if (input->is_key_pressed(KEY_A)) {
        move_left();
    }

    if (input->is_key_pressed(KEY_S)) {
        move_down();
    }

    if (input->is_key_pressed(KEY_D)) {
        move_right();
    }
}

 void Player::_bind_methods() {
     ClassDB::bind_method(D_METHOD("check_movement"), &Player::check_movement);
     ClassDB::bind_method(D_METHOD("move_up"), &Player::move_up);
     ClassDB::bind_method(D_METHOD("move_left"), &Player::move_left);
     ClassDB::bind_method(D_METHOD("move_down"), &Player::move_down);
     ClassDB::bind_method(D_METHOD("move_right"), &Player::move_right);
 }

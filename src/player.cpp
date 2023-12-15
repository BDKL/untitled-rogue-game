#include "player.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

 Player::Player() {

}

Player::~Player(){

}

void Player::start_player() {
    UtilityFunctions::print("i love gdextension");
}

 void Player::_bind_methods() {
   ClassDB::bind_method(D_METHOD("start_player"), &Player::start_player);
 }

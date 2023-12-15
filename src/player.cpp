#include "player.h"
// #include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
// #include <godot_cpp/variant/variant.hpp>

void Player::_ready() {
  UtilityFunctions::print("gdextension funciona agora?");
}

// this _bind_methods functions binds the methods from cpp to gdscript, so we
// are able to execute them inside gdscript and don't fall in the case of cpp
// code being ignored (more of this situation explained in notion)
// void Player::_bind_methods() {}

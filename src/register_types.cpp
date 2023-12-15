#include "register_types.h"
#include "player.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_player_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
  ClassDB::register_class<Player>();
}

void uninitialize_player_module(ModuleInitializationLevel p_level) {
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
project_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                     const GDExtensionClassLibraryPtr p_library,
                     GDExtensionInitialization *r_initialization) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initialization);

  init_obj.register_initializer(initialize_player_module);
  init_obj.register_terminator(uninitialize_player_module);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}

/*
 * When creating a new class and opening this file to add it to the project library, the steps should be:
 * 1. create the functions to initialize and uninitialize the class, just like the ones for the player class
 * 2. add two new lines to each of the functions, register_initializer for the initialize one and register_terminator for the uninitialize (just like lines 33 and 34)
 *
 * I think that should work. I hope :)
 *
 * and remember to also add the functions to the header register_types.h
 * */
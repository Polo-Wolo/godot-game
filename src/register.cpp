#include "register.hpp"

#include "gdextension_interface.h"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"
//==================
#include "BouncingSprite.hpp"
//==================

using  namespace godot;

//initializer for registering classes
void initialize(ModuleInitializationLevel p_level){
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }

    GDREGISTER_CLASS(BouncySprite);
}
//deinitializer
void uninitialize(ModuleInitializationLevel p_level){
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }
}

//entry point function for godot
extern "C" {
    GDExtensionBool GDE_EXPORT library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization * r_initialization
){
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address,p_library,r_initialization);

        init_obj.register_initializer(initialize);
        init_obj.register_terminator(uninitialize);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
     }
}
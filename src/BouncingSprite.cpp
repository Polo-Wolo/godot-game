#include "BouncingSprite.hpp"
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void BouncingSprite::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_speed", "s"), &BouncingSprite::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &BouncingSprite::get_speed);
    ClassDB::bind_method(D_METHOD("_on_direction_changed", "node"), &BouncingSprite::_on_direction_changed);

    ADD_PROPERTY(
        PropertyInfo(Variant::FLOAT, "speed"),
        "set_speed",
        "get_speed"
    );

    ADD_SIGNAL(MethodInfo(
        "direction_changed",
        PropertyInfo(Variant::OBJECT, "node", PROPERTY_HINT_RESOURCE_TYPE, "Node")
    ));
}

BouncingSprite::BouncingSprite()
{
    left_bounds = 0;
    right_bounds = 1152;
    top_bounds = 0;
    bottom_bounds = 648;
    speed = 200;
    velocity = Vector2(speed, speed);
}

BouncingSprite::~BouncingSprite() {}

void BouncingSprite::_ready() {
    UtilityFunctions::print("BouncingSprite ready!");
    // Connexion du signal au callback local
    connect("direction_changed", Callable(this, "_on_direction_changed"));
    // un peu débile de créer un signal pour revenir dans l'objet, mais permet de tester les signaux
}

void BouncingSprite::_process(double delta)
{
    Vector2 pos = get_position();

    Ref<Texture2D> tex = get_texture();
    if (!tex.is_valid())
        return; // éviter crash si pas de texture

    Vector2 size = tex->get_size();

    if (pos.x > right_bounds - size.x / 2)
    {
        if (velocity.x > 0)
            emit_signal("direction_changed", this);

        velocity.x = -speed;
    }
    else if (pos.x < left_bounds + size.x / 2)
    {
        if (velocity.x < 0)
            emit_signal("direction_changed", this);

        velocity.x = speed;
    }

    if (pos.y < top_bounds + size.y / 2)
    {
        if (velocity.y < 0)
            emit_signal("direction_changed", this);

        velocity.y = speed;
    }
    else if (pos.y > bottom_bounds - size.y / 2)
    {
        if (velocity.y > 0)
            emit_signal("direction_changed", this);

        velocity.y = -speed;
    }

    pos += velocity * delta;
    set_position(pos);
}

void BouncingSprite::set_speed(const float new_speed) {
    speed = new_speed;
    velocity = velocity.normalized() * speed;
}

float BouncingSprite::get_speed() const {
    return speed;
}

void BouncingSprite::_on_direction_changed(Node *node)
{
    UtilityFunctions::print("Direction changed from: ", node->get_name());
    
    Color color( UtilityFunctions::randf(), UtilityFunctions::randf(), UtilityFunctions::randf());

    // Vérifie que le node est bien un CanvasItem (donc qu'il a un self_modulate)
    CanvasItem *canvas_item = Object::cast_to<CanvasItem>(node);
    if (canvas_item) {
        canvas_item->set_self_modulate(color);
        UtilityFunctions::print("New color applied: ", color);
    } else
        UtilityFunctions::print("Node is not a CanvasItem, can't modulate color!");
}

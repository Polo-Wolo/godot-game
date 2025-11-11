#ifndef BOUNCING_SPRITE_H
#define BOUNCING_SPRITE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class BouncingSprite: public Sprite2D{

    GDCLASS(BouncingSprite,Sprite2D);

    public:
        float left_bounds;
        float right_bounds;
        float top_bounds;
        float bottom_bounds;
        Vector2 velocity;
        float speed;

    protected:
        static void _bind_methods();

    public:
        BouncingSprite();
        ~BouncingSprite();

        void set_speed(const float s);
        float get_speed() const;

        void _process(double delta) override;
        void _ready() override;
        void _on_direction_changed(Node *node);
};

}

#endif
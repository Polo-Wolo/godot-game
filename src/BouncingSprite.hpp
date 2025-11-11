#ifndef BOUNCING_SPRITE_H
#define BOUNCING_SPRITE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class BouncingSprite: public Sprite2D{

    GDCLASS(BouncingSprite,Sprite2D);

    public:
        double left_bounds;
        double right_bounds;
        double top_bounds;
        double buttom_bounds;
        Vector2 velocity;
        double speed;

    protected:
        static void _bind_methods();

    public:
        BouncingSprite();
        ~BouncingSprite();

        void _process(double delta) override;
};

}

#endif
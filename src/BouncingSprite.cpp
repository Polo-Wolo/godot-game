#include "BouncingSprite.hpp"


using namespace godot;

void BouncySprite::_bind_methods()
{
}

BouncySprite::BouncySprite()
{
    left_bounds = 0;
    right_bounds = 1000;
    top_bounds = 0;
    buttom_bounds = 800;
    speed = 50;
    velocity = Vector2(speed, speed);
}

BouncySprite::~BouncySprite()
{
}

void BouncySprite::_process(double delta)
{
    Vector2 pos = get_position();

    Vector2 size = get_texture()->get_size();
    //if position.x greater than bounds minus texturessize.x/2 if true invert speed vise vera
    if (pos.x > right_bounds-size.x/2)
    {
        velocity.x = -speed;
    }
    else if (pos.x < left_bounds+size.x/2)
    {
        velocity.x = speed;
    }

    if (pos.y < top_bounds+size.y/2)
    {
        velocity.y = speed;
    }
    else if (pos.y > buttom_bounds-size.y/2)
    {
        velocity.y = -speed;
    }
    //apply velocity to position
    pos += velocity * delta;
    //set position to new adjusted position
    set_position(pos);
}
#include <iostream>
#include "Wheel.hpp"

using cars::parts::Wheel;

Wheel::Wheel(core::Object *parent, int id, int diameter)
    : Object(parent)
    , id_(id)
    , diameter_(diameter)
{
}

void Wheel::punch(bool non_blocking)
{
    if (non_blocking)
    {
        post(new WheelPuncturedEvent(this));
    } else
    {
        send(new WheelPuncturedEvent(this));
    }
}

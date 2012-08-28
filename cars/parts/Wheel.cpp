#include <iostream>
#include "Wheel.hpp"

using cars::parts::Wheel;

Wheel::Wheel(core::Object *parent, int id, int diameter)
    : Object(parent)
    , id_(id)
    , diameter_(diameter)
{
}

void Wheel::punch()
{
    send(WheelPuncturedEvent(this));
}

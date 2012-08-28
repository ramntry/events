#include "Wheel.hpp"

using cars::parts::Wheel;

Wheel::Wheel(core::Object *parent, int diameter)
    : Object(parent)
    , diameter_(diameter)
{
}

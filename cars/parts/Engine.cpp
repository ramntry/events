#include "Engine.hpp"

using cars::parts::Engine;

Engine::Engine(Object *parent, int power)
    : Object(parent)
    , power_(power)
{
}

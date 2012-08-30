#include <core/Object.hpp>
#include "Event.hpp"

using core::Event;

Event::Event(core::Object *sender)
    : sender_(sender)
    , receiver_(sender)
{
    push();
}

void Event::push()
{
    hierarchy_.push_front(typeName());
}

Event::iterator Event::begin() const
{
    return hierarchy_.begin();
}

Event::iterator Event::end() const
{
    return hierarchy_.end();
}

void Event::process()
{
    receiver_->send(this);
}

void Event::up()
{
    receiver_ = receiver_->parent();
}

#include <stdexcept>
#include <core/EventQueue.hpp>
#include "Object.hpp"

using core::Object;
using core::Event;
using core::EventQueue;

Object::Object(Object *parent)
    : parent_(parent)
    , valid_iterator_(EventQueue::untrackedIterator())
{
    if (parent_ != 0)
    {
        me_in_childrenlist_ = parent_->addChild(this);
    }
}

Object::Object(core::Object const &)
{
    throw std::runtime_error("Copy constructor of Object is not implemented yet");
}

core::Object &Object::operator =(core::Object const &)
{
    throw std::runtime_error("Asign operator for Object is not implemented yet");
}

Object::~Object()
{
    if (parent_ != 0)
    {
        parent_->children_.erase(me_in_childrenlist_);
    }
    deleteChildren();
    deleteHandlers();
    EventQueue::excludeFromValid(valid_iterator_);
}

Object::ChildIterator Object::addChild(Object const *child)
{
    return children_.insert(children_.begin(), child);
}

void Object::deleteChildren()
{
    ChildIterator it = children_.begin();
    ChildIterator end = children_.end();
    for (; it != end; ++it)
    {
        (*it)->parent_ = 0;
        delete *it;
    }
    children_.clear();
}

void Object::deleteHandlers()
{
    EventHandlers::iterator it = handlers_.begin();
    EventHandlers::iterator end = handlers_.end();
    for (; it != end; ++it)
    {
        ChainOfHandlers::iterator sec_it = it->second.begin();
        ChainOfHandlers::iterator sec_end = it->second.end();
        for (; sec_it != sec_end; ++sec_it)
        {
            delete sec_it->first;
        }
    }
    handlers_.clear();
}

void Object::send(core::Event *event)
{
    Event::iterator it = event->begin();
    Event::iterator end = event->end();
    EventHandlers::iterator not_found_it = handlers_.end();
    for (; it != end; ++it)
    {
        EventHandlers::iterator find_it = handlers_.find(*it);
        if (find_it != not_found_it && !find_it->second.empty())
        {
            processChainOfHandlers(find_it->second, event);
            delete event;
            return;
        }
    }

    if (parent_ != 0)
    {
        event->up();
        event->process();
    } else
    {
        delete event;
    }
}

void Object::post(core::Event *event)
{
    valid_iterator_ = EventQueue::getInstance()->enque(event, valid_iterator_);
}

void Object::processChainOfHandlers(Object::ChainOfHandlers &chain, core::Event *event)
{
    ChainOfHandlers::iterator it = chain.begin();
    ChainOfHandlers::iterator end = chain.end();
    for (; it != end; ++it)
    {
        bool continuation_ret = (*it->first)(event);
        if (it->second == ForceBreak || (it->second == ByHandler && !continuation_ret))
        {
            break;
        }
    }
}

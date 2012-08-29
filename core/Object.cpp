#include "Object.hpp"

using core::Object;
using core::Event;

Object::Object(Object *parent)
    : parent_(parent)
{
    if (parent_ != 0)
    {
        parent_->addChild(this);
    }
}

Object::~Object()
{
    deleteChildren();
    deleteHandlers();
}

void Object::addChild(Object const *child)
{
    children_.push_back(child);
}

void Object::deleteChildren()
{
    ChildrenList::iterator it = children_.begin();
    ChildrenList::iterator end = children_.end();
    for (; it != end; ++it)
    {
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

void Object::send(const core::Event &event)
{
    Event::iterator it = event.begin();
    Event::iterator end = event.end();
    EventHandlers::iterator not_found_it = handlers_.end();
    for (; it != end; ++it)
    {
        EventHandlers::iterator find_it = handlers_.find(*it);
        if (find_it != not_found_it && !find_it->second.empty())
        {
            processChainOfHandlers(find_it->second, event);
            return;
        }
    }

    if (parent_ != 0)
    {
        parent_->send(event);
    }
}

void Object::processChainOfHandlers(Object::ChainOfHandlers &chain, core::Event const &event)
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

#include <core/Object.hpp>
#include "EventQueue.hpp"

using core::EventQueue;
using core::Event;

core::EventQueue *EventQueue::getInstance()
{
    static EventQueue instance;
    return &instance;
}

EventQueue::ValidIterator EventQueue::enque(Event const &event, ValidIterator position_assumption)
{
    events_.push_back(new Event(event));
    return sender_valid_controller_.insert(position_assumption, event.sender<Object>());
}

EventQueue::ValidIterator EventQueue::untrackedIterator()
{
    return getInstance()->sender_valid_controller_.end();
}

void EventQueue::excludeFromValid(EventQueue::ValidIterator iterator)
{
    if (iterator != untrackedIterator())
    {
        getInstance()->sender_valid_controller_.erase(iterator);
    }
}

void EventQueue::processAllEvents()
{
    EventContainer::iterator it = events_.begin();
    EventContainer::iterator end = events_.end();
    for (; it != end; ++it)
    {
        if (sender_valid_controller_.find((*it)->sender<Object>()) != untrackedIterator())
        {
            (*it)->process();
        }
    }
    deleteAllEvents();
}

void EventQueue::deleteAllEvents()
{
    EventContainer::iterator it = events_.begin();
    EventContainer::iterator end = events_.end();
    for (; it != end; ++it)
    {
        delete *it;
    }
    events_.clear();
}

EventQueue::~EventQueue()
{
    deleteAllEvents();
}

EventQueue::EventQueue()
{
}

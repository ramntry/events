#include "EventQueue.hpp"

using core::EventQueue;
using core::Event;

core::EventQueue *EventQueue::getInstance()
{
    static EventQueue instance;
    return &instance;
}

void EventQueue::enque(Event const &event)
{
    events_.push_back(new Event(event));
}

void EventQueue::processAllEvents()
{
    EventContainer::iterator it = events_.begin();
    EventContainer::iterator end = events_.end();
    for (; it != end; ++it)
    {
        (*it)->process();
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

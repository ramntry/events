#include <core/Object.hpp>
#include <core/Event.hpp>
#include "EventQueue.hpp"


using core::EventQueue;
using core::Event;

core::EventQueue *EventQueue::getInstance()
{
    static EventQueue instance;
    return &instance;
}

EventQueue::ValidIterator EventQueue::enque(Event *event, ValidIterator position_assumption)
{
    EventQueue *mp = getInstance();

    mp->events_.push_back(event);
    return mp->sender_valid_controller_.insert(position_assumption, event->sender<Object>());
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
    EventQueue *mp = getInstance();

    EventContainer::iterator it = mp->events_.begin();
    EventContainer::iterator end = mp->events_.end();
    for (; it != end; ++it)
    {
        if (mp->sender_valid_controller_.find((*it)->sender<Object>()) != untrackedIterator())
        {
            (*it)->process();
        } else
        {
            delete *it;
        }
    }
    mp->events_.clear();
}

EventQueue::~EventQueue()
{
    EventQueue *mp = getInstance();

    EventContainer::iterator it = mp->events_.begin();
    EventContainer::iterator end = mp->events_.end();
    for (; it != end; ++it)
    {
        delete *it;
    }
    mp->events_.clear();
}

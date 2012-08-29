#pragma once
#include <deque>
#include <core/Event.hpp>

namespace core {

class EventQueue : public MetaObject
{
public:
    typedef std::deque<Event *> EventContainer;

    virtual ~EventQueue();

    static EventQueue *getInstance();
    void enque(Event const &event);
    void processAllEvents();
    void deleteAllEvents();

protected:
    EventQueue();

    EventContainer events_;
};

}  // namespace core

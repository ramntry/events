#pragma once
#include <deque>
#include <set>
#include <core/MetaObject.hpp>

namespace core {

class Event;
class Object;

class EventQueue : public MetaObject
{
public:
    typedef std::deque<Event *> EventContainer;
    typedef std::set<Object *> ValidController;
    typedef ValidController::iterator ValidIterator;

    virtual ~EventQueue();

    static EventQueue *getInstance();
    static ValidIterator untrackedIterator();
    static void excludeFromValid(ValidIterator iterator);
    static ValidIterator enque(Event *event, ValidIterator position_assumption);
    static void processAllEvents();

protected:
    EventQueue() {}

    EventContainer events_;
    ValidController sender_valid_controller_;
};

}  // namespace core

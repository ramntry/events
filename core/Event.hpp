#pragma once
#include <deque>
#include <core/MetaObject.hpp>

namespace core {

class Object;

class Event : public MetaObject
{
public:
    typedef std::deque<const char *> EventHierarchy;
    typedef EventHierarchy::const_iterator iterator;

    Event(Object *sender);

    template <typename S>
    S *sender() const;

    template <typename R>
    R *receiver() const;

    void up();
    void process();

    iterator begin() const;
    iterator end() const;

protected:
    void push();

    Object *sender_;
    Object *receiver_;
    EventHierarchy hierarchy_;
};

template <typename S>
S *Event::sender() const
{
    return dynamic_cast<S *>(sender_);
}

template <typename R>
R *Event::receiver() const
{
    return dynamic_cast<R *>(receiver_);
}

#define EVENT_DECL(name, base) \
class name : public base \
{ \
public: \
    name(core::Object *sender) : base(sender) { push(); } \
}

}  // namespace core

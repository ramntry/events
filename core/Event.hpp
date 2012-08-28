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

    void push();
    iterator begin() const;
    iterator end() const;

protected:
    EventHierarchy hierarchy_;
    Object *sender_;
};

template <typename S>
S *Event::sender() const
{
    return dynamic_cast<S *>(sender_);
}

}  // namespace core

#pragma once
#include <deque>
#include <core/Object.hpp>

namespace core {

class Object;

class Event : public MetaObject
{
public:
    typedef std::deque<const char *> EventHierarchy;
    typedef EventHierarchy::const_iterator iterator;

    Event(Object *sender);

    void process();
    bool proceed();

    template <typename S> S *sender() const { return sender_->cast<S>(); }
    template <typename S> S *tryGetSender() const { return sender_->unsafeCast<S>(); }
    template <typename R> R *receiver() const { return receiver_->cast<R>(); }
    template <typename R> R *tryGetReceiver() const { return receiver_->unsafeCast<R>(); }

    iterator begin() const;
    iterator end() const;

protected:
    void push();
    Object *up();

    Object *sender_;
    Object *receiver_;
    EventHierarchy hierarchy_;
};

#define EVENT_DECL(name, base) \
class name : public base \
{ \
public: \
    name(core::Object *sender) : base(sender) { push(); } \
}

}  // namespace core

#pragma once
#include <list>
#include <map>
#include <string>
#include <core/MetaObject.hpp>
#include <core/Event.hpp>

namespace core {

class Object : public MetaObject
{
public:
    typedef std::list<Object const *> ChildrenList;
    struct EventHandler;
    typedef std::map<std::string, EventHandler *> EventHandlers;

    Object(Object *parent);
    virtual ~Object();

    Object *parent() { return parent_; }

protected:
    void addChild(Object const *child);
    void deleteChildren();
    void deleteHandlers();
    void send(Event const &event);
    template <typename E, typename H>
    void addHandler();

    Object *parent_;
    ChildrenList children_;
    EventHandlers handlers_;
};

struct Object::EventHandler
{
    virtual void operator ()(Event const &event) = 0;
};

template <typename E, typename H>
void Object::addHandler()
{
    handlers_[core::typeName<E>()] = new H;
}

}  // namespace core

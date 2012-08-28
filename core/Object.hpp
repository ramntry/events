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
    struct EventHandler;
    typedef std::map<std::string, EventHandler *> EventHandlers;
    typedef std::list<Object const *> ChildrenList;

    Object(Object *parent);
    virtual ~Object();

    Object *parent() const { return parent_; }

protected:
    void addChild(Object const *child);
    void deleteChildren();
    void deleteHandlers();

    template <typename E, typename H>
    void bind();
    void send(Event const &event);

    Object *parent_;
    ChildrenList children_;
    EventHandlers handlers_;
};

struct Object::EventHandler
{
    virtual void operator ()(Event const &event) = 0;
};

#define HANDLER_DECL(name) \
struct name : public core::Object::EventHandler \
{ \
    virtual void operator ()(core::Event const &event); \
}

template <typename E, typename H>
void Object::bind()
{
    handlers_[core::typeName<E>()] = new H;
}

}  // namespace core

#pragma once
#include <list>
#include <deque>
#include <map>
#include <string>
#include <core/MetaObject.hpp>
#include <core/Event.hpp>

namespace core {

class Object : public MetaObject
{
public:
    struct EventHandler;
    enum ContinuationPolicy { ByHandler = 0, ForceContinue, ForceBreak };
    typedef std::deque<std::pair<EventHandler *, ContinuationPolicy> > ChainOfHandlers;
    typedef std::map<std::string, ChainOfHandlers> EventHandlers;
    typedef std::list<Object const *> ChildrenList;

    Object(Object *parent);
    Object(Object const &src);
    Object &operator =(Object const &src);
    virtual ~Object();

    Object *parent() const { return parent_; }
    void send(Event const &event);
    void post(Event const &event);

protected:
    void addChild(Object const *child);
    void deleteChildren();
    void deleteHandlers();

    template <typename E> ChainOfHandlers &chainOfHandlers();
    template <typename E, typename H> void pushPreHandler(ContinuationPolicy policy = ByHandler);
    template <typename E, typename H> void pushPostHandler(ContinuationPolicy policy = ByHandler);
    template <typename E> void popPreHandler();
    template <typename E> void popPostHandler();
    void processChainOfHandlers(ChainOfHandlers &chain, Event const &event);

    Object *parent_;
    ChildrenList children_;
    EventHandlers handlers_;
};

struct Object::EventHandler
{
    virtual bool operator ()(Event const &event) = 0;
};

#define HANDLER_DECL(name) \
struct name : public core::Object::EventHandler \
{ \
    virtual bool operator ()(core::Event const &event); \
}

template <typename E>
Object::ChainOfHandlers &Object::chainOfHandlers()
{
    return handlers_[core::typeName<E>()];
}

template <typename E, typename H>
void Object::pushPreHandler(ContinuationPolicy policy)
{
    chainOfHandlers<E>().push_front(std::make_pair(new H, policy));
}

template <typename E, typename H>
void Object::pushPostHandler(ContinuationPolicy policy)
{
    chainOfHandlers<E>().push_back(std::make_pair(new H, policy));
}

template <typename E>
void Object::popPreHandler()
{
    ChainOfHandlers &chain = chainOfHandlers<E>();
    delete chain.front().first;
    chain.pop_front();
}

template <typename E>
void Object::popPostHandler()
{
    ChainOfHandlers &chain = chainOfHandlers<E>();
    delete chain.back().first;
    chain.pop_back();
}

}  // namespace core

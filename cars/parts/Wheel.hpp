#include <core/Object.hpp>
#include <core/Event.hpp>

namespace cars { namespace parts {

class Wheel : public core::Object
{
public:
    class WheelEvent;
    class WheelPuncturedEvent;

    Wheel(Object *parent, int id, int diameter);
    int diameter() { return diameter_; }
    int id() { return id_; }
    void punch();

protected:
    int id_;
    int diameter_;
};

class Wheel::WheelEvent : public core::Event
{
public:
    WheelEvent(core::Object *sender) : Event(sender) { push(); }
};

class Wheel::WheelPuncturedEvent : public Wheel::WheelEvent
{
public:
    WheelPuncturedEvent(core::Object *sender) : WheelEvent(sender) { push(); }
};

}}  // namespace cars::parts

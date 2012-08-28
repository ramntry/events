#include <core/Object.hpp>
#include <core/Event.hpp>

namespace cars { namespace parts {

class Wheel : public core::Object
{
public:
    EVENT_DECL(WheelEvent, core::Event);
    EVENT_DECL(WheelPuncturedEvent, WheelEvent);

    Wheel(Object *parent, int id, int diameter);
    int id() { return id_; }
    int diameter() { return diameter_; }

    void punch();

protected:
    int id_;
    int diameter_;
};

}}  // namespace cars::parts

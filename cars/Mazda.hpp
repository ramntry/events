#pragma once
#include <cars/Car.hpp>

namespace cars {

class Mazda : public Car
{
public:
    Mazda(Object *parent);
    void enableLowWheelEventsDetalisationMode();
    void enableBeepBeepWhenWheelEvent();

    HANDLER_DECL(WheelHandler);
    HANDLER_DECL(WheelPuncturedHandler);
};

}  // namespace cars

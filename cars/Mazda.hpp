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

protected:
    bool low_wheel_events_detalisation_mode_is_enabled_;
    bool beep_beep_when_wheel_event_;
};

}  // namespace cars

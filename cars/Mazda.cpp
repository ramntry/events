#include <iostream>
#include "Mazda.hpp"

using cars::Mazda;
using cars::parts::Wheel;
using core::Event;

Mazda::Mazda(Object *parent)
    : Car(parent, 200)
    , low_wheel_events_detalisation_mode_(false)
    , beep_beep_when_wheel_event_(false)
{
    for (int i = 0; i < 4; ++i)
    {
        addWheel(20);
    }
    pushPreHandler<Wheel::WheelPuncturedEvent, WheelPuncturedHandler>();
    pushPreHandler<Wheel::WheelEvent, WheelHandler>();
}

void Mazda::enableLowWheelEventsDetalisationMode()
{
    if (low_wheel_events_detalisation_mode_)
    {
        std::cout << "Mazda: Low wheel events detalisation mode is already enabled! Do nothing" << std::endl;
        return;
    }
    popPreHandler<Wheel::WheelPuncturedEvent>();
    low_wheel_events_detalisation_mode_ = true;
}

void Mazda::enableBeepBeepWhenWheelEvent()
{
    if (beep_beep_when_wheel_event_)
    {
        std::cout << "Mazda: Already beep-beep when wheel event! Well, do it twice (or even more!)" << std::endl;
    }
    pushPostHandler<Wheel::WheelEvent, BeepBeepHandler>();
    beep_beep_when_wheel_event_ = true;
}

bool Mazda::WheelHandler::operator ()(core::Event const &event)
{
    std::cout << "Mazda: something is wrong with wheel #" << event.sender<Wheel>()->id() << std::endl;
    return true;
}

bool Mazda::WheelPuncturedHandler::operator ()(core::Event const &event)
{
    std::cout << "Mazda: Wheel #" << event.sender<Wheel>()->id() << " was punctured!" << std::endl;
    return true;
}

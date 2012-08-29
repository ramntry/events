#include "Mazda.hpp"
#include <iostream>

using cars::Mazda;
using cars::parts::Wheel;
using core::Event;

Mazda::Mazda(Object *parent)
    : Car(parent, 200)
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
    popPreHandler<Wheel::WheelPuncturedEvent>();
}

void Mazda::enableBeepBeepWhenWheelEvent()
{
    pushPostHandler<Wheel::WheelEvent, BeepBeepHandler>();
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

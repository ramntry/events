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
    bind<Wheel::WheelPuncturedEvent, WheelPuncturedHandler>();
}

void Mazda::WheelPuncturedHandler::operator ()(core::Event const &event)
{
    std::cout << "Mazda: Wheel #" << event.sender<Wheel>()->id() << " was punctured!" << std::endl;
}

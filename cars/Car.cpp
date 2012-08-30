#include <iostream>
#include "Car.hpp"

using cars::Car;
using cars::parts::Wheel;

Car::Car(Object *parent, int power_of_engine)
    : Object(parent)
    , engine_(this, power_of_engine)
{
}

int Car::powerOfEngine() const
{
    return engine_.power();
}

int Car::numberOfWheels() const
{
    return wheels_.size();
}

void Car::addWheel(int diameter)
{
    wheels_.push_back(new Wheel(this, numberOfWheels(), diameter));
}

bool Car::BeepBeepHandler::operator ()(core::Event *event)
{
    std::cout << event->receiver<Car>()->typeName() << ": beep-beep!" << std::endl;
    return true;
}

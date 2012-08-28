#pragma once
#include <cars/Car.hpp>

namespace cars {

class Mazda : public Car
{
public:
    struct WheelPuncturedHandler;

    Mazda(Object *parent);
};

struct Mazda::WheelPuncturedHandler : public EventHandler
{
    virtual void operator ()(core::Event const &event);
};

}  // namespace cars

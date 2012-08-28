#pragma once
#include <cars/Car.hpp>

namespace cars {

class Mazda : public Car
{
public:
    Mazda(Object *parent);

    HANDLER_DECL(WheelPuncturedHandler);
};

}  // namespace cars

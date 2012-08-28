#pragma once
#include <vector>
#include <cars/parts/Wheel.hpp>
#include <cars/parts/Engine.hpp>

namespace cars {

class Car : public core::Object
{
public:
    typedef std::vector<parts::Wheel *> Wheels;

    Car(Object *parent, int power_of_engine);
    int powerOfEngine() const;
    int numberOfWheels() const;
    Wheels &wheels() { return wheels_; }

protected:
    void addWheel(int diameter);

    parts::Engine *engine_;
    Wheels wheels_;
};

}  // namespace cars

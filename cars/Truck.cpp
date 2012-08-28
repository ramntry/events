#include "Truck.hpp"

using cars::Truck;

Truck::Truck(Object *parent)
    : Car(parent, 120)
{
    for (int i = 0; i < 6; ++i)
    {
        addWheel(17);
    }
}

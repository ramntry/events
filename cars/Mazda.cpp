#include "Mazda.hpp"

using cars::Mazda;

Mazda::Mazda(Object *parent)
    : Car(parent, 200)
{
    for (int i = 0; i < 4; ++i)
    {
        addWheel(20);
    }
}

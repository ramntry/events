#include <iostream>
#include <vector>
#include <cars/Mazda.hpp>
#include <cars/Truck.hpp>

int main()
{
    std::vector<cars::Car *> two_cars;
    two_cars.push_back(new cars::Mazda(0));
    two_cars.push_back(new cars::Truck(0));

    for (int i = 0; i < 2; ++i)
    {
        cars::Car *curr = two_cars[i];
        std::cout <<
            "typeid: " << curr->typeName() << '\n' <<
            "number of wheels: " << curr->numberOfWheels() << '\n' <<
            "power of engine: " << curr->powerOfEngine() << '\n' <<
        std::endl;
    }

    two_cars.front()->wheels()[2]->punch();

    delete two_cars.front();
    delete two_cars.back();
}

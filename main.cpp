#include <iostream>
#include <vector>
#include <core/EventQueue.hpp>
#include <cars/Mazda.hpp>
#include <cars/Truck.hpp>

using namespace cars;
using namespace core;

void eventHandlingTest(Mazda *mazda, bool non_blocking)
{
    mazda->wheels()[1]->punch(non_blocking);

    std::cout << "\nEnable low wheel events detalisation mode:" << std::endl;
    mazda->enableLowWheelEventsDetalisationMode();
    mazda->wheels()[2]->punch(non_blocking);

    std::cout << "\nAdd beep-beep handler:" << std::endl;
    mazda->enableBeepBeepWhenWheelEvent();
    mazda->wheels()[3]->punch(non_blocking);

    if (non_blocking)
    {
        std::cout << "\nprocess all events:\n" << std::endl;
        EventQueue::processAllEvents();
    }
}

int main()
{
    std::vector<Car *> two_cars;
    two_cars.push_back(new Mazda(0));
    two_cars.push_back(new Truck(0));

    for (int i = 0; i < 2; ++i)
    {
        Car *curr = two_cars[i];
        std::cout <<
            "typeid: " << curr->typeName() << '\n' <<
            "number of wheels: " << curr->numberOfWheels() << '\n' <<
            "power of engine: " << curr->powerOfEngine() << '\n' <<
        std::endl;
    }

    Mazda *mazda = two_cars.front()->cast<Mazda>();

    std::cout << "\n\n=== Blocking test of event handling ===\n" << std::endl;
    eventHandlingTest(mazda, false);

    std::cout << "\n\n=== Non-blocking test of event handling ===\n" << std::endl;
    eventHandlingTest(mazda, true);

    delete mazda->wheels()[0];
    delete two_cars.back()->wheels()[4];

    mazda->wheels()[1]->punch(true);
    delete two_cars.front();
    std::cout << "\nAnd now I'm nothing to do, because sender of posted events already is gone" << std::endl;
    EventQueue::processAllEvents();

    Car::Wheels &truck_wheels = two_cars.back()->wheels();
    truck_wheels[0]->punch();
    truck_wheels[1]->punch();
    truck_wheels[1]->punch(true);
    truck_wheels[2]->punch(true);
    truck_wheels[3]->punch(true);
    truck_wheels[3]->punch();

    delete two_cars.back();
}

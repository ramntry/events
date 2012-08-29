#include <iostream>
#include <vector>
#include <core/EventQueue.hpp>
#include <cars/Mazda.hpp>
#include <cars/Truck.hpp>

void eventHandlingTest(cars::Mazda *mazda, bool non_blocking)
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
        core::EventQueue::getInstance()->processAllEvents();
    }
}

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

    cars::Mazda *mazda = dynamic_cast<cars::Mazda *>(two_cars.front());

    std::cout << "\n\n=== Blocking test of event handling ===\n" << std::endl;
    eventHandlingTest(mazda, false);

    std::cout << "\n\n=== Non-blocking test of event handling ===\n" << std::endl;
    eventHandlingTest(mazda, true);

    delete two_cars.front();
    delete two_cars.back();
}

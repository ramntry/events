#pragma once
#include <core/Object.hpp>

namespace cars { namespace parts {

class Engine : public core::Object
{
public:
    Engine(Object *parent, int power);
    int power() { return power_; }

private:
    int power_;
};

}}  // namespace cars::parts

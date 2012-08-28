#include <typeinfo>
#include "MetaObject.hpp"

using core::MetaObject;

const char *MetaObject::typeName() const
{
    return typeid(*this).name();
}

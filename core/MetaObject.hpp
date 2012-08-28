#pragma once
#include <typeinfo>

namespace core {

class MetaObject
{
public:
    virtual ~MetaObject() {}
    const char *typeName() const;
};

template <typename T>
const char *typeName()
{
    return typeid(T).name();
}

}  // namespace core

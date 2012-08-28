#pragma once

namespace core {

class MetaObject
{
public:
    virtual ~MetaObject() {}
    const char *typeName() const;
};

}  // namespace core

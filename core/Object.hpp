#pragma once
#include <list>
#include <core/MetaObject.hpp>

namespace core {

class Object : public MetaObject
{
public:
    typedef std::list<Object const *> ChildrenList;

    Object(Object *parent);
    virtual ~Object();

protected:
    void addChild(Object const *child);
    void deleteChildren();

    Object *parent_;
    ChildrenList children_;
};

}  // namespace core

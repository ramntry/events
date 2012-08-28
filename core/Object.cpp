#include "Object.hpp"

using core::Object;

Object::Object(Object *parent)
    : parent_(parent)
{
    if (parent_ != 0)
    {
        parent_->addChild(this);
    }
}

Object::~Object()
{
    deleteChildren();
}

void Object::addChild(Object const *child)
{
    children_.push_back(child);
}

void Object::deleteChildren()
{
    ChildrenList::iterator it = children_.begin();
    ChildrenList::iterator end = children_.end();
    for (; it != end; ++it)
    {
        delete *it;
    }
    children_.clear();
}

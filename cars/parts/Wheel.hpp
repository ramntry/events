#include <core/Object.hpp>

namespace cars { namespace parts {

class Wheel : public core::Object
{
public:
    Wheel(Object *parent, int diameter);
    int diameter() { return diameter_; }

protected:
    int diameter_;
};

}}  // namespace cars::parts

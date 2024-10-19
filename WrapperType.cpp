#include "WrapperType.hpp"

std::ostream& operator<<(std::ostream& out, const WrapperType value)
{
#define VAL(a) case a: { return out << #a; break; }
    switch (value)
    {
        VAL(Cardboard);
        VAL(Paper);
        VAL(Plastic);
    default:
    {
        return out << "?";
        break;
    }
    }
#undef VAL
}

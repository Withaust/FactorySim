#pragma once

#include <ostream>

enum WrapperType : char
{
    Cardboard = 0,
    Paper,
    Plastic,
    Max
};

std::ostream& operator<<(std::ostream& out, const WrapperType value);

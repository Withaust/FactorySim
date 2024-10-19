#pragma once

#include "WrapperType.hpp"

struct Product
{
    char Name = '?';
    int Weight = 0;
    WrapperType Wrapper = WrapperType::Cardboard;
};

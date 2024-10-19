#include "Util.hpp"

char IndexToCapitalLetter(int Index)
{
    if (Index >= 0 && Index <= 25)
    {
        return Index + 65;
    }
    return '?';
}

char IndexToLowercaseLetter(int FactoryIndex)
{
    if (FactoryIndex >= 0 && FactoryIndex <= 25)
    {
        return FactoryIndex + 97;
    }
    return '?';
}

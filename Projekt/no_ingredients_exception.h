#pragma once
#include <stdexcept>

class NoIngredientsException : public std::invalid_argument {
public:
    NoIngredientsException();
};
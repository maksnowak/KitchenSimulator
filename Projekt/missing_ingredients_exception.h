#pragma once
#include <stdexcept>
#include <vector>
#include "ingredient.h"

class MissingIngredientsException : public std::runtime_error {
public:
    MissingIngredientsException();
};
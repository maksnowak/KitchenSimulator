#include "no_ingredients_exception.h"

NoIngredientsException::NoIngredientsException() : std::invalid_argument("The list of ingredients must not be empty.") {}

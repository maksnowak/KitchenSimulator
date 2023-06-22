#include "missing_ingredients_exception.h"

MissingIngredientsException::MissingIngredientsException() : std::runtime_error("Cannot make a recipe - there are missing ingredients") {};
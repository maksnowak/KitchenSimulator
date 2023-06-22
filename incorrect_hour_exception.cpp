#include "incorrect_hour_exception.h"

IncorrectHourException::IncorrectHourException(unsigned short int hour) : std::invalid_argument("Incorrect hour value: " + std::to_string(hour)) {}
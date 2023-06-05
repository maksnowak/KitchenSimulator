#include "incorrect_hour_exception.h"

IncorrectMinuteException::IncorrectMinuteException(unsigned short int hour) : std::invalid_argument("Incorrect hour value: " + std::to_string(hour)) {}
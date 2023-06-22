#include "incorrect_minute_exception.h"

IncorrectMinuteException::IncorrectMinuteException(unsigned short int minute) : std::invalid_argument("Incorrect minute value: " + std::to_string(minute)) {}
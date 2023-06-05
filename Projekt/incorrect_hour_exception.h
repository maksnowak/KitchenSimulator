#pragma once
#include <stdexcept>

class IncorrectHourException : public std::invalid_argument {
public:
    IncorrectHourException(unsigned short int hour);
};
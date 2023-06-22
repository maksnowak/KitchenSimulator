#pragma once
#include <stdexcept>

class IncorrectMinuteException : public std::invalid_argument {
public:
    IncorrectMinuteException(unsigned short int minute);
};

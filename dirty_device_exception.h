#pragma once
#include <stdexcept>

class DirtyDeviceException : public std::runtime_error {
public:
    DirtyDeviceException();
};
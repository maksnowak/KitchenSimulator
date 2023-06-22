#pragma once
#include <stdexcept>
#include <vector>
#include "device.h"

class MissingDevicesException : public std::runtime_error {
public:
    MissingDevicesException();
};
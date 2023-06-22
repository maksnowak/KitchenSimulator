#include "dirty_device_exception.h"

DirtyDeviceException::DirtyDeviceException() : std::runtime_error("Cannot make a recipe - one of the devices is dirty") {}
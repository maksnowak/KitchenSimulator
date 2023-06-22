#include "missing_devices_exception.h"

MissingDevicesException::MissingDevicesException() : std::runtime_error("Cannot make a recipe - there are missing devices") {};
#include "device.h"

Device::Device(std::string name, State type) : name(name), type(type) {}

std::string Device::getName() {
    return name;
}

State Device::getType() {
    return type;
}

void Device::setName(std::string new_name) {
    name = new_name;
}

void Device::setType(State new_type) {
    type = new_type;
}

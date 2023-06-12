#include "device.h"

Device::Device(std::string name, State state) : name(name), state(state) {}

std::string Device::getName() {
    return name;
}

State Device::getState() {
    return state;
}

void Device::setName(std::string new_name) {
    name = new_name;
}

void Device::setState(State new_state) {
    state = new_state;
}

bool Device::operator==(const Device& other_device) const {
    return name == other_device.name;
}

bool Device::operator!=(const Device& other_device) const {
    return !(*this == other_device);
}
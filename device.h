#pragma once
#include <iostream>

enum class State {
    clean,
    dirty
};

class Device {
private:
    std::string name;
    State state;
public:
    Device(std::string name, State state);
    std::string getName();
    State getState();
    void setName(std::string name);
    void setState(State state);
    bool operator==(const Device& other_device) const;
    bool operator!=(const Device& other_device) const;
};


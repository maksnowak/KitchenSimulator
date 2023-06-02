#pragma once
#include <iostream>

enum class State {
    clean,
    dirty
};

class Device {
private:
    std::string name;
    State type;
public:
    Device(std::string name, State type);
    std::string getName();
    State getType();
    void setName(std::string name);
    void setType(State type);
};

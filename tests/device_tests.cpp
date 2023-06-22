#include "catch_amalgamated.hpp"
#include "../device.h"

// Example device


TEST_CASE("Device tests", "[device]") {
    Device device("Blender", State::clean);
    CHECK(device.getName() == "Blender");
    CHECK(device.getState() == State::clean);

    SECTION("Setting new values") {
        device.setName("Pot");
        device.setState(State::dirty);
        CHECK(device.getName() == "Pot");
        CHECK(device.getState() == State::dirty);
    }

    SECTION("Comparing two different devices") {
        Device other_device("Oven", State::clean);
        CHECK(device != other_device);
        CHECK_FALSE(device == other_device);
    }

    SECTION("Comparing two different devices") {
        Device other_device("Oven", State::clean);
        CHECK(device != other_device);
        CHECK_FALSE(device == other_device);
    }
}

#include "catch_amalgamated.hpp"
#include "../device.h"

// Example device
Device device("Blender", State::clean);

TEST_CASE("Device tests", "[device]") {
    CHECK(device.getName() == "Blender");
    CHECK(device.getType() == State::clean);

    SECTION("Setting new values") {
        device.setName("Pot");
        device.setType(State::dirty);
        CHECK(device.getName() == "Pot");
        CHECK(device.getType() == State::dirty);
    }
}

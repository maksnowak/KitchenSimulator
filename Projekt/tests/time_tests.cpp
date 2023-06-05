#include "catch_amalgamated.hpp"
#include "../time.h"
#include "../incorrect_hour_exception.h"
#include "../incorrect_minute_exception.h"

TEST_CASE("Time unit tests", "[time]") {
    Time time(8, 0);
    CHECK(time.getHour() == 8);
    CHECK(time.getMinute() == 0);

    SECTION("Setting new values") {
        time.setHour(12);
        time.setMinute(30);
        CHECK(time.getHour() == 12);
        CHECK(time.getMinute() == 30);
    }

    SECTION("Skipping time by a given number of minutes") {
        time.skip_by(30);
        CHECK(time.getHour() == 8);
        CHECK(time.getMinute() == 30);
        time.skip_by(60);
        CHECK(time.getHour() == 9);
        CHECK(time.getMinute() == 30);
        time.skip_by(155);
        CHECK(time.getHour() == 12);
        CHECK(time.getMinute() == 5);
        time.skip_by(727);
        CHECK(time.getHour() == 0);
        CHECK(time.getMinute() == 12);
    }

    SECTION("Skipping time to a set hour and minute") {
        time.skip_to(12, 30);
        CHECK(time.getHour() == 12);
        CHECK(time.getMinute() == 30);
        time.skip_to(9, 30);
        CHECK(time.getHour() == 9);
        CHECK(time.getMinute() == 30);
        time.skip_to(0, 5);
        CHECK(time.getHour() == 0);
        CHECK(time.getMinute() == 5);
    }

    SECTION("Skipping time to incorrect values") {
        CHECK_THROWS_AS(time.skip_to(24, 0), IncorrectHourException);
        CHECK_THROWS_AS(time.skip_to(0, 60), IncorrectMinuteException);
        CHECK_THROWS_AS(time.skip_to(24, 60), IncorrectHourException);
        CHECK_THROWS_AS(time.skip_to(25, 60), IncorrectHourException);
        CHECK_THROWS_AS(time.skip_to(24, 61), IncorrectHourException);
        CHECK_THROWS_AS(time.skip_to(25, 61), IncorrectHourException);
    }
}
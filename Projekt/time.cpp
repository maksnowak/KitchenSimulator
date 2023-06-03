#include "time.h"

Time::Time(unsigned short int hour, unsigned short int minute) : hour(hour), minute(minute) {}

unsigned short int Time::getHour() {
    return hour;
}

unsigned short int Time::getMinute() {
    return minute;
}

void Time::setHour(unsigned short int new_hour) {
    hour = new_hour;
}

void Time::setMinute(unsigned short int new_minute) {
    minute = new_minute;
}

void Time::skip_to(unsigned short int new_hour, unsigned short int new_minute) {
    if (new_hour < 24 && new_minute < 60) {
        hour = new_hour;
        minute = new_minute;
    }
    // else throw exception (to be implemented)
}

void Time::skip_by(unsigned short int new_minute) {
    if (minute + new_minute < 60) {
        minute += new_minute;
    }
    else {
        hour += (minute + new_minute) / 60;
        minute = (minute + new_minute) % 60;
    }
}

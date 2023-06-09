#include "time.h"
#include "incorrect_hour_exception.h"
#include "incorrect_minute_exception.h"

Time::Time(unsigned short int hour, unsigned short int minute){
    setHour(hour);
    setMinute(minute);
}

unsigned short int Time::getHour() {
    return hour;
}

unsigned short int Time::getMinute() {
    return minute;
}

void Time::setHour(unsigned short int new_hour) {
    if (new_hour >= 24) {
        throw IncorrectHourException(new_hour);
    }
    hour = new_hour;
}

void Time::setMinute(unsigned short int new_minute) {
    if (new_minute >= 60) {
        throw IncorrectMinuteException(new_minute);
    }
    minute = new_minute;
}

void Time::skip_to(unsigned short int new_hour, unsigned short int new_minute) {
    if (new_hour < 24 && new_minute < 60) {
        hour = new_hour;
        minute = new_minute;
    }
    else {
        if (new_hour >= 24) {
            throw IncorrectHourException(new_hour);
        }
        else {
            throw IncorrectMinuteException(new_minute);
        }
    }
}

void Time::skip_by(unsigned short int new_minute) {
    minute += new_minute;
    if (minute >= 60) {
        hour += minute / 60;
        minute %= 60;
    }
    if (hour >= 24) {
        hour %= 24;
    }
}

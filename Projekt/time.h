#pragma once

class Time {
private:
    unsigned short int hour;
    unsigned short int minute;
public:
    Time(unsigned short int hour, unsigned short int minute);
    unsigned short int getHour();
    unsigned short int getMinute();
    void setHour(unsigned short int hour);
    void setMinute(unsigned short int minute);
    void skip_to(unsigned short int hour, unsigned short int minute);
    void skip_by(unsigned short int minute);
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
};
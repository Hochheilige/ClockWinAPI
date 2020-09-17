#include "Time.h"

void Time::Increase() {
    ++seconds;

    if (IsSecondsLimit()) {
        seconds = 0;
        ++minutes;
    }
     
    if (IsMinutesLimit()) {
        minutes = 0;
        ++hours;
    }

    if (IsHoursLimit()) {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
}

void Time::PrintCurrentTimeStd() const {
    std::cout << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(hours) << ':'
              << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(minutes) << ':'
              << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(seconds) << std::endl;
}

void Time::PrintCurrentTimeWnd() const {
}

Time Time::CurrentTime() const {
    return {hours, minutes, seconds};
}

#include <../lib/DS3231/DS3231.h>
#include <Wire.h>
#include <time.h>


#ifndef CLOCK_H
#define CLOCK_H


class Clock
{
    private:
        DS3231 m_rtc;

        uint8_t m_hour;
        uint8_t m_minute;
        uint8_t* m_time_group[2] = {&m_hour, &m_minute};
    
    public:
        Clock();
        uint8_t* time_group();
        void read_time();
        void set_new_time(uint8_t hour, uint8_t minute);
        uint8_t is_valid_time(int8_t digit, uint8_t driver_index);
        void initial_rtc_setup();
};

#endif

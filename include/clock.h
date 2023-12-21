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
        uint8_t m_second;
        uint8_t* m_time_array[3] = {&m_hour, &m_minute, &m_second};   // array of pointers is necessary to store references, not copies
        uint8_t m_time_digits[4];
    
    public:
        Clock();
        uint8_t* time();
        void read_time();
        uint8_t* time_digit();
        void slice_time_into_digits();
        void set_new_time(uint8_t hour, uint8_t minute, uint8_t second = 0);
        uint8_t is_valid_time(int8_t digit, uint8_t driver_index);
        void initial_rtc_setup();
};

#endif

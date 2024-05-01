#include <../lib/DS3231/DS3231.h>
#include <Wire.h>
#include <time.h>


#ifndef CLOCK_H
#define CLOCK_H


class Clock
{
    private:
        DS3231 m_rtc;
        RTCDateTime m_date_time;
        uint8_t m_hour;
        uint8_t m_minute;
        uint8_t* m_time[2] = { &m_hour, &m_minute };
    
    public:
        Clock();
        uint8_t* time();
        void read_rtc_time();
        void set_new_time(uint8_t hour, uint8_t minute);
        uint8_t new_time_validation(int8_t digit, uint8_t time_segment);
        void initial_rtc_setup();
};

#endif

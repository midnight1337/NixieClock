#include "../include/clock.h"

Clock::Clock() : m_rtc() 
{
    m_rtc.begin();
}

uint8_t* Clock::time()
{
    return *m_time_array;
}

void Clock::read_time()
{
    RTCDateTime time = m_rtc.getDateTime();
    m_hour = time.hour;
    m_minute = time.minute;
    m_second = time.second;
}

uint8_t Clock::time_digit(uint8_t index) { return m_time_digits[index]; }

void Clock::slice_time_into_digits()
{
    m_time_digits[0] = (m_hour / 10) % 10;
    m_time_digits[1] = m_hour % 10;
    m_time_digits[2] = (m_minute / 10) % 10;
    m_time_digits[3] = m_minute % 10;
}

void Clock::initial_rtc_setup()
{
    // Compile this method for the RTC first time ever setup, then compile one again without this method.
    m_rtc.setDateTime(0, 0, 0, 0, 0, 0);
}

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

uint8_t* Clock::time_digit() { return m_time_digits; }

void Clock::slice_time_into_digits()
{
    m_time_digits[0] = (m_hour / 10) % 10;
    m_time_digits[1] = m_hour % 10;
    m_time_digits[2] = (m_minute / 10) % 10;
    m_time_digits[3] = m_minute % 10;
}

// This is not done yet
uint8_t Clock::is_valid_time(int8_t digit, uint8_t driver_index)
{
    uint8_t valid_digit;

    switch (driver_index)
    {
        case 1:
            if (digit > 2) { valid_digit = 0; }
            else if (digit < 0) { valid_digit = 2; }
            else { valid_digit = digit; }
            break;

        case 2:
            if (m_time_digits[0] == 2)
            {
                if (digit > 3) { valid_digit = 0; }
                else if (digit < 0) { valid_digit = 3; }
                else { valid_digit = digit; }
            }
            else
            {
                if (digit > 9) { valid_digit = 0; }
                else if (digit < 0) { valid_digit = 9; }
                else { valid_digit = digit; }
            }
            break;
        
        case 3:
            break;
    }
return valid_digit;
}

void Clock::set_new_time(uint8_t hour, uint8_t minute, uint8_t second)
{
    m_rtc.setDateTime(0, 0, 0, hour, minute, second);
}

void Clock::initial_rtc_setup()
{
    // Compile this method for the RTC first time ever setup, then compile one again without this method.
    m_rtc.setDateTime(0, 0, 0, 0, 0, 0);
}

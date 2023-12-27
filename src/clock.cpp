#include "../include/clock.h"

Clock::Clock() : m_rtc() 
{
    m_rtc.begin();
}

uint8_t* Clock::time_group() { return *m_time_group; }

void Clock::read_time()
{
    RTCDateTime time = m_rtc.getDateTime();
    m_hour = time.hour;
    m_minute = time.minute;
}

void Clock::set_new_time(uint8_t hour, uint8_t minute)
{
    m_rtc.setDateTime(0, 0, 0, hour, minute, 0);
}

uint8_t Clock::is_valid_time(int8_t digit, uint8_t driver_index)
{
    // Change cases to according to driver group
    uint8_t valid_digit;

    switch (driver_index)
    {
        case 1:
            if (digit > 2) { valid_digit = 0; }
            else if (digit < 0) { valid_digit = 2; }
            else { valid_digit = digit; }
            break;

        case 2:
            if (digit == 2)
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

void Clock::initial_rtc_setup()
{
    // Compile this method for the RTC first time ever setup, then compile one again without this method.
    m_rtc.setDateTime(0, 0, 0, 0, 0, 0);
}

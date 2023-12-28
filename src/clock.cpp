#include "../include/clock.h"

Clock::Clock() : m_rtc() 
{
    m_rtc.begin();
    // initial_rtc_setup();
}

uint8_t* Clock::time_group()
{ 
    // this variable simply points into two elements, current hour and minute
    return *m_time_group;
}

void Clock::read_time()
{
    m_time = m_rtc.getDateTime();
    m_hour = m_time.hour;
    m_minute = m_time.minute;
}

void Clock::set_new_time(uint8_t hour, uint8_t minute)
{
    m_rtc.setDateTime(0, 0, 0, hour, minute, 0);
}

uint8_t Clock::is_valid_time(int8_t digit, uint8_t digit_group)
{
    uint8_t valid_digit;

    switch (digit_group)
    {
        case 0:
            if (digit > 23) { valid_digit = 0; }
            else if (digit < 0) { valid_digit = 23; }
            else { valid_digit = digit; }
            break;
        
        case 1:
            if (digit > 59) { valid_digit = 0; }
            else if (digit < 0) { valid_digit = 59; }
            else { valid_digit = digit; }
            break;

        default:
            break;
    }
    
    return valid_digit;
}

void Clock::initial_rtc_setup()
{
    /* Compile this method for the RTC first time ever setup, then compile once again without this method. */
    m_rtc.setDateTime(0, 0, 0, 0, 0, 0);
}

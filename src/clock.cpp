#include "../include/clock.h"

Clock::Clock() : m_rtc() 
{
    m_rtc.begin();
}

uint8_t* Clock::time()
{ 
    /* This variable simply points into array that contains hour and minute, { "HH", "MM" } */
    return *m_time;
}

void Clock::read_rtc_time()
{
    m_date_time = m_rtc.getDateTime();
    m_hour = m_date_time.hour;
    m_minute = m_date_time.minute;
}

void Clock::update_rtc_time()
{
    m_rtc.setDateTime(__DATE__, m_hour, m_minute);
}

void Clock::set_new_time(uint8_t hour, uint8_t minute)
{
    m_rtc.setDateTime(__DATE__, hour, minute);
}

uint8_t Clock::new_time_validation(int8_t digit, uint8_t time_segment)
{
    /* 
    int8_t digit = Desired digit to be displayed that needs validation
    uint8_t time_segment = Time format represented as group (HH = 0, MM = 1)
    */
    uint8_t valid_digit;

    switch (time_segment)
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
    /* Compile this method for the RTC first time ever setup, it will set clock time as compilation time. Then compile once again without this method. */
    m_rtc.setDateTime(__DATE__, __TIME__);
}

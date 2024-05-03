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

uint8_t Clock::new_time_validation(int8_t time, uint8_t time_segment)
{
    /* 
    int8_t time = Desired time to be displayed on a particular time segment tubes that needs validation, it depends on a 24h time format.
    uint8_t time_segment = Time segment represented as a particular group {0: 'HH', 1: 'MM'}
    */
    uint8_t valid_time;

    switch (time_segment)
    {
        case 0:
            if (time > 23) { valid_time = 0; }
            else if (time < 0) { valid_time = 23; }
            else { valid_time = time; }
            break;
        
        case 1:
            if (time > 59) { valid_time = 0; }
            else if (time < 0) { valid_time = 59; }
            else { valid_time = time; }
            break;
    }
    
    return valid_time;
}

void Clock::initial_rtc_setup()
{
    /* Compile this method for the RTC first time ever setup, it will set clock time as compilation time. Then compile once again without this method. */
    m_rtc.setDateTime(__DATE__, __TIME__);
}

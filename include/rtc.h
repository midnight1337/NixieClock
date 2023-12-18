#ifndef RTC_H
#define RTC_H


class Rtc
{
    private:
        int m_hour;
        int m_minute;
        int m_second;
        int* time_array[3] = {&m_hour, &m_minute, &m_second};   // array of pointers is necessary to store references, not copies
    
    public:
        Rtc();
        int** time();
        void read_time();
};

#endif

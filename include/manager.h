#include <Arduino.h>
#include "nixie_driver.h"
#include "clock.h"
#include "switch.h"
#include "hardware_pinout.h"


#ifndef MANAGER_H
#define MANAGER_H


// This const variable represents a count of time segments -> HH:MM {0: 'HH', 1: 'MM'}
const uint8_t TIME_SEGMENTS = 2;

class Manager
{
    private:
        NixieDriver m_driver_0;
        NixieDriver m_driver_1;
        NixieDriver m_driver_2;
        NixieDriver m_driver_3;
        NixieDriver* m_drivers[4] = { &m_driver_0, &m_driver_1, &m_driver_2, &m_driver_3 }; // array of pointers is necessary to store references, not copies
        NixieDriver* m_hour_segment_drivers[TIME_SEGMENTS] = { &m_driver_0, &m_driver_1 };
        NixieDriver* m_minute_segment_drivers[TIME_SEGMENTS] = { &m_driver_2, &m_driver_3 };
        NixieDriver* m_time_segments_drivers[TIME_SEGMENTS][TIME_SEGMENTS] = { *m_hour_segment_drivers, *m_minute_segment_drivers };
        
        Switch m_switch_edit;
        Switch m_switch_previous;
        Switch m_switch_next;
        
        Clock m_clock;
        
    public:
        Manager();
        void run();
        void setup();
        void edit_time_mode();
        void display_time();
        void run_tubes_test();
        void tubes_blinking(uint8_t how_many_times = 3, uint16_t delay_time = 200, int8_t ommit_time_segment = -1);
        void turn_on_tubes(int8_t ommit_time_segment = -1);
        void turn_off_tubes(int8_t ommit_time_segment = -1);
        int run_timer();
};

#endif

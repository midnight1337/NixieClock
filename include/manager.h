#include "Arduino.h"
#include "nixie_driver.h"
#include "clock.h"
#include "switch.h"
#include "hardware_pinout.h"


#ifndef MANAGER_H
#define MANAGER_H


class Manager
{
    private:
        
        NixieDriver m_driver_0;
        NixieDriver m_driver_1;
        NixieDriver m_driver_2;
        NixieDriver m_driver_3;
        NixieDriver* m_drivers[4] = { &m_driver_0, &m_driver_1, &m_driver_2, &m_driver_3 }; // array of pointers is necessary to store references, not copies
        NixieDriver* m_hour_digit_drivers[2] = { &m_driver_0, &m_driver_1 };
        NixieDriver* m_minute_digit_drivers[2] = { &m_driver_2, &m_driver_3 };
        NixieDriver* m_digit_drivers_time_group[2][2] = { m_hour_digit_drivers[0], m_hour_digit_drivers[1], 
                                                        m_minute_digit_drivers[0], m_minute_digit_drivers[1] };

        Switch m_switch_menu;
        Switch m_switch_previous;
        Switch m_switch_next;
        
        Clock m_clock;
        
    public:
        Manager();
        void run();
        void setup();
        void menu_mode();

        void display_time();
        void run_tubes_test();
        void tubes_blinking(uint8_t how_many_times = 3, uint16_t delay_time = 200, int8_t ommit_digit_group = -1);
        void turn_on_tubes(int8_t ommit_digit_group = -1);
        void turn_off_tubes(int8_t ommit_digit_group = -1);
};

#endif

#include "nixie_driver.h"
#include "rtc.h"
#include "hardware_pinout.h"

#ifndef MANAGER_H
#define MANAGER_H

class Manager
{
    private:
        NixieDriver m_driver_1;
        NixieDriver m_driver_2;
        NixieDriver m_driver_3;
        NixieDriver m_driver_4;
        Rtc m_rtc;

    public:
        Manager();
        void run();
        void setup();

        void run_tubes_test_on_power_on();
        void tubes_blinking();
        void turn_on_tube(int id, bool all_tubes = false);
        void turn_off_tube(int id, bool all_tubes = false);
};

#endif

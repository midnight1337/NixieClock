#include <Arduino.h>

#ifndef DRIVER_BASE_H
#define DRIVER_BASE_H


class DriverBase
{
    protected:
        String m_label;
        const int m_pin_a;
        const int m_pin_b;
        const int m_pin_c;
        const int m_pin_d;
    
    public:
        DriverBase(String label, int pin_a, int pin_b, int pin_c, int pin_d);
        void set_pinout_state(bool pin_a, bool pin_b, bool pin_c, bool pin_d);
        virtual ~DriverBase() = 0;
};

#endif

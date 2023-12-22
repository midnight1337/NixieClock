#include <Arduino.h>

#ifndef NIXIE_DRIVER_H
#define NIXIE_DRIVER_H


class NixieDriver
{
    private:
        const int m_pin_a;
        const int m_pin_b;
        const int m_pin_c;
        const int m_pin_d;
    
    public:
        NixieDriver(int pin_a, int pin_b, int pin_c, int pin_d);
        void set_pinout_state(uint8_t bitset);
        uint8_t truth_table(int8_t digit);
};

#endif

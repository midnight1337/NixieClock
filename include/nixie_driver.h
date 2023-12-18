
#ifndef NIXIE_DRIVER_H
#define NIXIE_DRIVER_H

class NixieDriver
{
    private:
        int m_pin_a;
        int m_pin_b;
        int m_pin_c;
        int m_pin_d;
    
    public:
        NixieDriver(int pin_a, int pin_b, int pin_c, int pin_d);
        void set_pinout_state(int pin_a, int pin_b, int pin_c, int pin_d);
};

#endif

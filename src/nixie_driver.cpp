#include "../include/nixie_driver.h"


NixieDriver::NixieDriver(int pin_a, int pin_b, int pin_c, int pin_d): m_pin_a(pin_a), m_pin_b(pin_b), m_pin_c(pin_c), m_pin_d(pin_d)
{

}

void NixieDriver::set_pinout_state(int pin_a, int pin_b, int pin_c, int pin_d)
{
    m_pin_a = pin_a;
    m_pin_b = pin_b;
    m_pin_c = pin_c;
    m_pin_d = pin_d;
}
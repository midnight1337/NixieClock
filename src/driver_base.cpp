#include "../include/driver_base.h"

DriverBase::DriverBase(String label, int pin_a, int pin_b, int pin_c, int pin_d): m_label(label), m_pin_a(pin_a), m_pin_b(pin_b), m_pin_c(pin_c), m_pin_d(pin_d)
{

}

void DriverBase::set_pinout_state(bool pin_a, bool pin_b, bool pin_c, bool pin_d)
{
    digitalWrite(m_pin_a, pin_a);
    digitalWrite(m_pin_b, pin_b);
    digitalWrite(m_pin_c, pin_c);
    digitalWrite(m_pin_d, pin_d);
}

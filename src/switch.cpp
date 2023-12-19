#include "../include/switch.h"

Switch::Switch(int pin) : m_pin(pin) {}

bool Switch::event()
{
    bool is_event = digitalRead(m_pin) == true ? true : false;
    return is_event;
}

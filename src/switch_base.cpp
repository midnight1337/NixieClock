#include "../include/switch_base.h"

SwitchBase::SwitchBase(int pin) : m_pin(pin) {}

bool SwitchBase::event()
{
    bool is_event = digitalRead(m_pin) == true ? true : false;
    return is_event;
}

#include <Arduino.h>

#ifndef SWITCH_H
#define SWITCH_H


class Switch
{
    protected:
        int m_pin;

    public:
        Switch(int pin);
        bool event();
};

#endif

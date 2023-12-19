#include <Arduino.h>

#ifndef SWITCHBASE_H
#define SWITCHBASE_H


class SwitchBase
{
    protected:
        String label;
        int m_pin;

    public:
        SwitchBase(int pin);
        bool event();
        virtual void function();
        virtual ~SwitchBase() = 0;
};

#endif

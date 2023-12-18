#include "nixie_driver.h"
#include "rtc.h"

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
};

#endif

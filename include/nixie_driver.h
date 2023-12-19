#include "driver_base.h"

#ifndef NIXIE_DRIVER_H
#define NIXIE_DRIVER_H

class NixieDriver : public DriverBase
{
    public: 
        NixieDriver(int pin_a, int pin_b, int pin_c, int pin_d);
};

#endif

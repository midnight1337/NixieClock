#include "../include/manager.h"


Manager::Manager() : 
m_driver_1("Driver 1", Pin_A1, Pin_B1, Pin_C1, Pin_D1),
m_driver_2("Driver 1", Pin_A2, Pin_B2, Pin_C2, Pin_D2),
m_driver_3("Driver 1", Pin_A3, Pin_B3, Pin_C3, Pin_D3),
m_driver_4("Driver 1", Pin_A4, Pin_B4, Pin_C4, Pin_D4)
{
    
}

void Manager::run()
{
    /*
        1.Read time
        2.Decode every digit from time into truth table of Drivers
        3.Setup driver state so nixie tube turns for corresponding digit
    */
   m_rtc.read_time();
}

void Manager::setup()
{
    /*
        Initialise pinout here??
    */
}

void Manager::run_tubes_test_on_power_on()
{
    /*
        Display number from 0-9 on every tube
    */
}

void Manager::tubes_blinking()
{

}

void Manager::turn_on_tube(int id, bool all_tubes = false)
{
    if (all_tubes)
    {
        // ...
        return;
    }


}

void Manager::turn_off_tube(int id, bool all_tubes = false)
{
    if (all_tubes)
    {
        // ...
        return;
    }


}

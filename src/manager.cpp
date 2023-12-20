#include "../include/manager.h"


Manager::Manager() : 
m_driver_0(Pin_A1, Pin_B1, Pin_C1, Pin_D1),
m_driver_1(Pin_A2, Pin_B2, Pin_C2, Pin_D2),
m_driver_2(Pin_A3, Pin_B3, Pin_C3, Pin_D3),
m_driver_3(Pin_A4, Pin_B4, Pin_C4, Pin_D4),
m_switch_menu(Pin_EDIT_AND_NEXT),
m_switch_previous(Pin_DOWN),
m_switch_next(Pin_UP),
m_rtc()
{}


void Manager::run()
{
    /*
        1.Read time
        2.Decode every digit from time into truth table of Drivers
        3.Setup driver state so nixie tube turns for corresponding digit
        4.Check for events
    */
    m_rtc.read_time();
    event();
}

void Manager::setup()
{
    /*
        Initialise board pinout
    */
    pinMode(Pin_EDIT_AND_NEXT, INPUT);

    for (int i = 0; i <= 16; i++)
    {
        pinMode(i, OUTPUT);
    }

    run_tubes_test();
}

void Manager::event()
{
    if (m_switch_menu.event())
    {
        bool is_pressed = false;
        int driver_index = 0;
        int start_timer = 0;
        int stop_timer = 0;
        int idle_time = 0;
        uint8_t number = 0;
        uint8_t bitset = 0b0000;
        NixieDriver* ptr_current_driver = m_drivers[driver_index];
        //NixieDriver* ptr_current_driver = *(m_drivers + driver_index);
        
        tubes_blinking();

        while (true)
        {
            // All tubes are blinking, despite selected one by driver_index

            if (m_switch_next.event())
            {
                // Verify if time format allows increment time digit
                bitset = ptr_current_driver->truth_table(number);
                ptr_current_driver->set_pinout_state(bitset);
            }

            if (m_switch_previous.event())
            {
                // Verify if time format allows decrement time digit
                bitset = ptr_current_driver->truth_table(number);
                ptr_current_driver->set_pinout_state(bitset);
            }

            // 1. Start timer if condition met
            if (m_switch_menu.event() && !is_pressed) { is_pressed = true; start_timer = millis(); }

            // 2. Update stop timer if condition met
            if (m_switch_menu.event() && is_pressed) { stop_timer = millis(); }

            // 3. If button was released after it was pressed, measure idle_time and determine further instruction
            if (!m_switch_menu.event() && is_pressed)
            {
                idle_time = stop_timer - start_timer;
                
                // Exit from menu mode, or change tube driver
                if (idle_time >= 1000) 
                {
                    // rtc.set date time
                    return; 
                }
                else
                { 
                    driver_index = ( driver_index >= 3 ) ? 0 : driver_index + 1;
                    ptr_current_driver = m_drivers[driver_index];
                    start_timer = 0;
                    stop_timer = 0; 
                }
            }
        }

        tubes_blinking();

    }
}

void Manager::run_tubes_test()
{
    /*
        Display digit from 0-9 on every tube, when device powered on.
    */
   uint8_t bitset;

   for (int i = 0; i < 10; i++)
   {
        bitset = m_drivers[0]->truth_table(i);

        m_drivers[0]->set_pinout_state(bitset);
        m_drivers[1]->set_pinout_state(bitset);
        m_drivers[2]->set_pinout_state(bitset);
        m_drivers[3]->set_pinout_state(bitset);

        delay(200);
   }
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

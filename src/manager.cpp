#include "../include/manager.h"


Manager::Manager() : 
m_driver_0(Pin_A0, Pin_B0, Pin_C0, Pin_D0),
m_driver_1(Pin_A1, Pin_B1, Pin_C1, Pin_D1),
m_driver_2(Pin_A2, Pin_B2, Pin_C2, Pin_D2),
m_driver_3(Pin_A3, Pin_B3, Pin_C3, Pin_D3),
m_switch_menu(Pin_MENU),
m_switch_previous(Pin_DOWN),
m_switch_next(Pin_UP),
m_clock()
{}


void Manager::run()
{
    /*
        1.Read time (read current time from rtc and slice it into each digit)
        2.Display time (decode each digit according to drivers truth table, set corresponding state to digit on driver)
        3.Check for events
    */
    m_clock.read_time();
    display_time();
    event();
}

void Manager::setup()
{
    pinMode(Pin_MENU, INPUT);
    // Can't set pinMode for other switches (Pin_UP, Pin_DOWN) because they are not digital, but it doesn't interfere with reading its state directly as HIGH or LOW

    for (int i = 0; i <= 16; i++) { pinMode(i, OUTPUT); }
}

void Manager::display_time()
{
    uint8_t bitset;
    uint8_t digit;

    for (int i = 0; i < 4; i++)
    {
        //digit = m_clock.time_digit()[i];
        bitset = m_drivers[i]->truth_table(digit);
        m_drivers[i]->set_pinout_state(bitset);
    }
}

void Manager::event()
{
    if (m_switch_menu.event())
    {
        bool is_pressed = false;
        int start_timer = 0;
        int stop_timer = 0;
        int idle_time = 0;
        int8_t new_digit = 0;
        int8_t new_time = 0;
        uint8_t bitset = 0b0000;
        uint8_t drivers_time_group_index = 0;
        uint8_t new_time_buffer[2];
        NixieDriver* current_driver;

        for (int i = 0; i < 2; i++) { new_time_buffer[i] = m_clock.time()[i]; }
        
        tubes_blinking();

        while (true)
        {
            //tubes_blinking(1, 500, driver_index);

            if (m_switch_next.event() || m_switch_previous.event())
            {
                // Get current clock digits (HH or MM) and do proper action
                if (m_switch_next.event()) { new_time = new_time_buffer[drivers_time_group_index]++; }
                else if (m_switch_previous.event()) { new_time = new_time_buffer[drivers_time_group_index]--; }
                else { break; }
                
                // Verify new clock digits and get valid one
                new_time = m_clock.is_valid_time(new_time, drivers_time_group_index);
                new_time_buffer[drivers_time_group_index] = new_time;

                // Set new clock digits into drivers according to drivers group
                for (int i = 0; i < 2; i++)
                {
                    current_driver = m_drivers_time_group[drivers_time_group_index + i][i];

                    // Determine digit weigth according to current driver from drivers group
                    new_digit = (i & 1 == 0) ? new_time % 10 : (new_time / 10) % 10;

                    // Set new clock digits into drivers
                    bitset = current_driver->truth_table(new_digit);
                    current_driver->set_pinout_state(bitset);
                }
            }
            
            /* THESE EVENT INSTRUCTIONS BELOW ARE WRONG BRO */
            // 1. Start timer if condition met
            if (m_switch_menu.event() && !is_pressed) 
            { 
                is_pressed = true; 
                start_timer = millis(); 
            }

            // 2. Update stop timer if condition met
            if (m_switch_menu.event() && is_pressed) { stop_timer = millis(); }

            // 3. If button was released after it was pressed, measure idle_time and determine further instruction
            if (!m_switch_menu.event() && is_pressed)
            {
                idle_time = stop_timer - start_timer;
                
                // Save new time in rtc and exit from menu mode, or change tube driver and continue edit mode
                if (idle_time >= 1000) 
                {
                    uint8_t new_hour = (new_time_buffer[0] * 10) + new_time_buffer[1];
                    uint8_t new_minute = (new_time_buffer[2] * 10) + new_time_buffer[3];

                    m_clock.set_new_time(new_hour, new_minute);

                    return; 
                }
                else
                { 
                    drivers_time_group_index = ( drivers_time_group_index >= 1 ) ? 0 : drivers_time_group_index + 1;
                    is_pressed = false;
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
    /* Display digit from 0-9 on every tube */
   uint8_t bitset;

   for (int i = 0; i < 10; i++)
   {
        bitset = m_drivers[0]->truth_table(i);

        for (int j = 1; j < 4; j++) { m_drivers[j]->set_pinout_state(bitset); }

        delay(200);
   }
}

void Manager::tubes_blinking(uint8_t how_many_times, uint16_t delay_time, int8_t ommit_driver_index)
{
    for (int i = 0; i < how_many_times; i++)
    {
        turn_off_tubes(ommit_driver_index);

        delay(delay_time);

        turn_on_tubes(ommit_driver_index);

        delay(delay_time);
    }
}

void Manager::turn_on_tubes(int8_t ommit_driver_index)
{
    //  Get truth table for each driver's digit
    uint8_t bitset;
    uint8_t digit;

    for (int i = 0; i < 4; i++)
    {
        if (i == ommit_driver_index) { continue; }
        
        //digit = m_clock.time_digit()[i];
        bitset = m_drivers[i]->truth_table(digit);
        m_drivers[i]->set_pinout_state(bitset);
    }
}

void Manager::turn_off_tubes(int8_t ommit_driver_index)
{
    //  Return 0b1111 so drivers are off
    uint8_t bitset = m_drivers[0]->truth_table(-1);

    for (int i = 0; i < 4; i++)
    {
        if (i == ommit_driver_index) { continue; }

        m_drivers[i]->set_pinout_state(bitset);
    }
}

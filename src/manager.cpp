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
    NixieDriver* current_driver;
    uint8_t bitset;
    uint8_t digit;
    uint8_t time;

    // Loop over drivers group
    for (int i = 0; i < 2; i++)
    {
        time = m_clock.time_group()[i];

        // Loop over each driver in current drivers group
        for (int j = 0; j < 2; j++)
        {
            current_driver = m_digit_drivers_time_group[i][j];

            digit = (j == 0) ? (time / 10) & 10 : time % 10;

            bitset = current_driver->truth_table(digit);

            current_driver->set_pinout_state(bitset);
        }
    }
}

void Manager::event()
{
    if (m_switch_menu.event())
    {
        NixieDriver* current_driver;
        uint8_t new_time_buffer[2];
        uint8_t digit_group_index = 0;
        uint8_t bitset = 0b0000;
        int8_t new_digit = 0;
        int8_t new_time = 0;
        int start_timer = 0;
        int stop_timer = 0;
        int idle_time = 0;
        bool is_pressed = false;
        
        // Initialise time buffer with current time hour and minute
        for (int i = 0; i < 2; i++) { new_time_buffer[i] = m_clock.time_group()[i]; }
        
        tubes_blinking();

        while (true)
        {
            tubes_blinking(1, 500, digit_group_index);

            if (m_switch_next.event() || m_switch_previous.event())
            {
                // Get current clock time based on digit group index, and do proper action based on pressed switch
                if (m_switch_next.event()) { new_time = new_time_buffer[digit_group_index]++; }
                else if (m_switch_previous.event()) { new_time = new_time_buffer[digit_group_index]--; }
                
                // Verify new time and get valid one according to each digit group time logic
                new_time = m_clock.is_valid_time(new_time, digit_group_index);

                // Save valid time into time buffer
                new_time_buffer[digit_group_index] = new_time;

                // Set new digits into drivers according to digit group
                for (int i = 0; i < 2; i++)
                {
                    current_driver = m_digit_drivers_time_group[digit_group_index][i];

                    // Determine digit weigth according to current driver from digit group
                    // For first driver we need a decimal digit and for second driver a unit digit
                    new_digit = (i == 0) ? (new_time / 10) % 10 : new_time % 10;

                    // Set new clock digit into driver
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
                    digit_group_index = ( digit_group_index >= 1 ) ? 0 : digit_group_index + 1;
                    is_pressed = false;
                    start_timer = 0;
                    stop_timer = 0;
                }
            }
        }
        tubes_blinking(5);
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

void Manager::tubes_blinking(uint8_t how_many_times, uint16_t delay_time, int8_t ommit_digit_group)
{
    for (int i = 0; i < how_many_times; i++)
    {
        turn_off_tubes(ommit_digit_group);

        delay(delay_time);

        turn_on_tubes(ommit_digit_group);

        delay(delay_time);
    }
}

void Manager::turn_on_tubes(int8_t ommit_digit_group)
{
    NixieDriver* current_driver;
    uint8_t time;
    uint8_t digit;
    uint8_t bitset;

    // Loop over drivers time group
    for (int i = 0; i < 2; i++)
    {
        if (i == ommit_digit_group) { continue; }
        
        time = m_clock.time_group()[i];

        // Loop over each driver in particular time group
        for (int j = 0; j < 2; j++)
        {
            current_driver = m_digit_drivers_time_group[i][j];
            
            // Determine digit weigth according to current driver
            digit = (j == 0) ? (time / 10) % 10 : time % 10;

            // Set clock digit into driver
            bitset = current_driver->truth_table(digit);

            current_driver->set_pinout_state(bitset);
        }
    }
}

void Manager::turn_off_tubes(int8_t ommit_digit_group)
{
    //  Digit -1 passed into truth table, returns a 0b1111 bitset which sets none driver output.
    NixieDriver* current_driver;
    int8_t digit = -1;
    uint8_t bitset = m_drivers[0]->truth_table(digit);
    
    for (int i = 0; i < 2; i++)
    {
        if (i == ommit_digit_group) { continue; }

        for (int j = 0; j < 2; j++)
        {
            current_driver = m_digit_drivers_time_group[i][j];

            current_driver->set_pinout_state(bitset);
        }
    }
}

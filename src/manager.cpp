#include "../include/manager.h"


Manager::Manager() : 
m_driver_0(Pin_A0, Pin_B0, Pin_C0, Pin_D0),
m_driver_1(Pin_A1, Pin_B1, Pin_C1, Pin_D1),
m_driver_2(Pin_A2, Pin_B2, Pin_C2, Pin_D2),
m_driver_3(Pin_A3, Pin_B3, Pin_C3, Pin_D3),
m_switch_edit(Pin_MENU),
m_switch_previous(Pin_DOWN),
m_switch_next(Pin_UP),
m_clock()
{}

void Manager::run()
{
    m_clock.read_rtc_time();
    m_clock.update_rtc_time();
    display_time();
    edit_time_mode();
}

void Manager::setup()
{
    /* 
        Set pins from 0 to 16 as OUTPUT, as they are used for driving Nixie drivers,
        Can't set pinMode as INPUT for switches: Pin_UP and Pin_DOWN because they are not digital but analog pins. 
        However it doesn't interfere with reading its state directly as HIGH or LOW.
    */
    pinMode(Pin_MENU, INPUT);

    for (int i = 0; i <= 16; i++)
    {
        pinMode(i, OUTPUT);
    }

    // m_clock.initial_rtc_setup();
}

void Manager::display_time()
{
    NixieDriver* driver;
    uint8_t bitset;
    uint8_t digit;
    uint8_t time;

    // Loop over time segments drivers
    for (int i = 0; i < TIME_SEGMENTS; i++)
    {
        // Determine time segment related to a time segments drivers
        time = m_clock.time()[i];

        // Loop over each driver in a current time segments drivers
        for (int j = 0; j < TIME_SEGMENTS; j++)
        {
            // Get current driver
            driver = m_time_segments_drivers[i][j];

            // Determine digit weigth according to current driver
            digit = (j == 0) ? (time / 10) % 10 : time % 10;

            // Get bitset related to a desired digit from a driver's truth table
            bitset = driver->truth_table(digit);

            // Set driver pinouts according to a bitset
            driver->set_driver_mode(bitset);
        }
    }
}

void Manager::edit_time_mode()
{
    if (m_switch_edit.event())
    {
        NixieDriver* driver;
        uint8_t new_time_buffer[TIME_SEGMENTS];
        uint8_t time_segment_index = 0;
        uint8_t bitset = 0b0000;
        int8_t new_digit = 0;
        int8_t new_time = 0;
        int idle_time = 0;
        bool is_pressed = false;
        
        // Initialise new_time_buffer with actual RTC time
        for (int i = 0; i < TIME_SEGMENTS; i++) 
        {
            new_time_buffer[i] = m_clock.time()[i];
        }
        
        tubes_blinking();

        while (true)
        {
            tubes_blinking(1, 500, time_segment_index);

            // Add or subtract value from time buffer in given time segment
            if (m_switch_next.event() || m_switch_previous.event())
            {
                if (m_switch_next.event()) 
                {
                    new_time = new_time_buffer[time_segment_index]++;
                }
                else if (m_switch_previous.event())
                {
                    new_time = new_time_buffer[time_segment_index]--;
                }

                new_time = m_clock.new_time_validation(new_time, time_segment_index);

                new_time_buffer[time_segment_index] = new_time;

                // Set new time into drivers digits according to current time segment
                for (int i = 0; i < TIME_SEGMENTS; i++)
                {
                    driver = m_time_segments_drivers[time_segment_index][i];

                    // Determine digit weigth according to current driver from digit group, For first driver we need a decimal digit and for second driver a unit digit
                    new_digit = (i == 0) ? (new_time / 10) % 10 : new_time % 10;

                    // Set new clock digit into driver
                    bitset = driver->truth_table(new_digit);

                    driver->set_driver_mode(bitset);
                }
            }

            // Start timer
            if (m_switch_edit.event() && !is_pressed) 
            { 
                idle_time = run_timer();
                is_pressed = true; 
            }

            // If menu button was pressed, measure idle_time and determine further instruction
            if (is_pressed)
            {   
                // If idle time is greater than 1s, then save new time into rtc and exit menu mode
                if (idle_time > 1000) 
                {
                    m_clock.set_new_time(new_time_buffer[0], new_time_buffer[1]);
                    tubes_blinking();

                    return; 
                }
                // If idle time is less than 1s, then change time segment of drivers and continue editing
                else
                { 
                    time_segment_index = ( time_segment_index >= 1 ) ? 0 : time_segment_index + 1;
                    is_pressed = false;
                }
            }
        }
        tubes_blinking(2);
    }
}

int Manager::run_timer()
{
    int start_timer = millis();
    int stop_timer = millis();
    int idle_time = 0;

    // Hold the switch more than 1 second to meet idle_time expectations for exit condition
    while (m_switch_edit.event())
    {
        if (idle_time > 1000)
        {
            break;
        }

        stop_timer = millis();
        idle_time = stop_timer - start_timer;
    }

    return idle_time;
}

void Manager::tubes_blinking(uint8_t how_many_times, uint16_t delay_time, int8_t ommit_time_segment)
{
    for (int i = 0; i < how_many_times; i++)
    {
        turn_off_tubes(ommit_time_segment);

        delay(delay_time);

        turn_on_tubes(ommit_time_segment);

        delay(delay_time);
    }
}

void Manager::turn_on_tubes(int8_t ommit_time_segment)
{
    NixieDriver* current_driver;
    uint8_t time;
    uint8_t digit;
    uint8_t bitset;

    for (int i = 0; i < TIME_SEGMENTS; i++)
    {
        if (i == ommit_time_segment)
        {
            continue;
        }
        
        time = m_clock.time()[i];

        for (int j = 0; j < TIME_SEGMENTS; j++)
        {
            current_driver = m_time_segments_drivers[i][j];
            
            digit = (j == 0) ? (time / 10) % 10 : time % 10;

            bitset = current_driver->truth_table(digit);

            current_driver->set_driver_mode(bitset);
        }
    }
}

void Manager::turn_off_tubes(int8_t ommit_time_segment)
{
    NixieDriver* current_driver;
    int8_t digit = -1;
    uint8_t bitset = m_drivers[0]->truth_table(digit);
    
    for (int i = 0; i < TIME_SEGMENTS; i++)
    {
        if (i == ommit_time_segment)
        {
            continue;
        }

        for (int j = 0; j < TIME_SEGMENTS; j++)
        {
            current_driver = m_time_segments_drivers[i][j];

            current_driver->set_driver_mode(bitset);
        }
    }
}

void Manager::run_tubes_test()
{
    /* Test nixie tubes by displaying digits from 0 to 9 on each tube */
   uint8_t bitset;

   for (int i = 0; i < 10; i++)
   {
        bitset = m_drivers[0]->truth_table(i);

        for (int j = 1; j < 4; j++) 
        {
            m_drivers[j]->set_driver_mode(bitset);
        }

        delay(200);
   }
}

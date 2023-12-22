/* DEFINED DIGITAL MICROCONTROLLER PINOUTS */

/*
WIRING SETUP FOR ARDUINO PRO MINI

*/


enum DriversPinout
{
    // MCU -> SN74141N_0
    Pin_A0 = 3,  // LSB
    Pin_B0 = 4,
    Pin_C0 = 5,
    Pin_D0 = 6,  // MSB

    // MCU -> SN74141N_1
    Pin_A1 = 7,  // LSB
    Pin_B1 = 8,
    Pin_C1 = 9,
    Pin_D1 = 10,  // MSB

    // MCU -> SN74141N_2
    Pin_A2 = 11,  // LSB
    Pin_B2 = 12,
    Pin_C2 = 13,
    Pin_D2 = 14, // A0, MSB

    // MCU -> SN74141N_3
    Pin_A3 = 15, // LSB, (Analog 1)
    Pin_B3 = 16, // (Analog 2)
    Pin_C3 = 0,  // (PCB Analog 6 is wired with D0 (RX) so A6 can't be set as output directly??)
    Pin_D3 = 1, // MSB, (PCB Analog 7 is wired with D1 (TX) so A7 can't be set as output directly??)
};


enum MicroswitchPinout
{
    // // MCU -> microswitch
    Pin_MENU = 17,  // Analog 3, Edit Mode; Next digit.
    Pin_DOWN = 20,  // Analog 6, Digit down
    Pin_UP = 21,    // Analog 7, Digit up
};

// This enum is unused so far
enum ClockPinout
{
    Pin_SDA = 18,   // Analog 4
    Pin_SCL = 19,   // Analog 5
};

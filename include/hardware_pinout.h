/* DEFINED DIGITAL MICROCONTROLLER VARIABLES */


enum DriversPinout
{
    // MCU -> SN74141N_1
    Pin_A1 = 3,  // LSB
    Pin_B1 = 4,
    Pin_C1 = 5,
    Pin_D1 = 6,  // MSB

    // MCU -> SN74141N_2
    Pin_A2 = 7,  // LSB
    Pin_B2 = 8,
    Pin_C2 = 9,
    Pin_D2 = 10,  // MSB

    // MCU -> SN74141N_3
    Pin_A3 = 11,  // LSB
    Pin_B3 = 12,
    Pin_C3 = 13,
    Pin_D3 = 14, // A0, MSB

    // MCU -> SN74141N_4
    Pin_A4 = 15, // LSB, (Analog 1)
    Pin_B4 = 16, // (Analog 2)
    Pin_C4 = 0,  // (PCB Analog 6 is wired with D0 (RX) so A6 can't be set as output directly??)
    Pin_D4 = 1, // MSB, (PCB Analog 7 is wired with D1 (TX) so A7 can't be set as output directly??)
};


enum MicroswitchPinout
{
    // // MCU -> microswitch
    Pin_EDIT_AND_NEXT = 17,  // Analog 3, Edit Mode; Next digit.
    Pin_DOWN = 20,  // Analog 6, Digit down
    Pin_UP = 21,    // Analog 7, Digit up
};

/* DEFINED DIGITAL MICROCONTROLLER VARIABLES */

/*
    SN74141N
*/

// MCU -> SN74141N_0
const int A1 = 3;  // LSB
const int B1 = 4;
const int C1 = 5;
const int D1 = 6;  // MSB

// MCU -> SN74141N_1
const int A2 = 7;  // LSB
const int B2 = 8;
const int C2 = 9;
const int D2 = 10;  // MSB

// MCU -> SN74141N_2
const int A3 = 11;  // LSB
const int B3 = 12;
const int C3 = 13;
const int D3 = 14; // A0, MSB

// MCU -> SN74141N_3
const int A4 = 15; // LSB, (Analog 1)
const int B4 = 16; // (Analog 2)
const int C4 = 0;  // (PCB Analog 6 is wired with D0 (RX) so A6 can't be set as output directly??)
const int D4 = 1;  // MSB, (PCB Analog 7 is wired with D1 (TX) so A7 can't be set as output directly??)

// MCU -> microswitch
const int switch_next = 17; // A3, Edit Mode; Next digit.
const int switch_down = 20; // Onboard A6, Digit down
const int switch_up = 21; // Onboard A7, Digit up
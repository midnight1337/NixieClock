#include "../include/nixie_driver.h"

NixieDriver::NixieDriver(int pin_a, int pin_b, int pin_c, int pin_d) : 
m_pin_a(pin_a), 
m_pin_b(pin_b), 
m_pin_c(pin_c), 
m_pin_d(pin_d) 
{}

void NixieDriver::set_driver_mode(uint8_t bitset)
{
    /* Set pinouts of driver by given bitset, which represents a digit to be displayed */

    digitalWrite(m_pin_a, bitset & 0b0001); // LSB
    digitalWrite(m_pin_b, bitset & 0b0010);
    digitalWrite(m_pin_c, bitset & 0b0100);
    digitalWrite(m_pin_d, bitset & 0b1000); // MSB
}

uint8_t NixieDriver::truth_table(int8_t digit)
{
    /*
        Determine the truth table for driving a particular digit,
        Pinouts on PCB are reversed, in that case we need to reverse the truth table for drivers
    */
    uint8_t bitset = 0b0000;

    switch (digit)
    {
    case 0x00: // 0
        bitset = 0b0000;
        break;
    case 0x01: // |1001| => |0001|, bitset of '9' will display '1' on tube
        bitset = 0b1001;
        break;
    case 0x02: // 8 => 2
        bitset = 0b1000;
        break;
    case 0x03: // 7 => 3
        bitset = 0b1110;
        break;
    case 0x04: // 6 => 4
        bitset = 0b0110;
        break;
    case 0x05: // 5 => 5
        bitset = 0b0101;
        break;
    case 0x06: // 4 => 6
        bitset = 0b0100;
        break;
    case 0x07: // 3 => 7
        bitset = 0b0011;
        break;
    case 0x08: // 2 => 8
        bitset = 0b0010;
        break;
    case 0x09: // 1 => 9
        bitset = 0b0001;
        break;
    default:    // display off if out of range
        bitset = 0b1111;
        break;
    }
    
    return bitset;
}

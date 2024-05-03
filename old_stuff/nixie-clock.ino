/**
 * @title: Nixie Clock
 * @author midnight1337
 * @brief This is my very first code implementation of Nixie Clock, no OOP here so it's messy, but it worked just fine.
 * @date: 17-07-2021
*/
#include <DS3231.h>
#include <Wire.h>


// Digital 2 is free
// Analog 3 is POT middle pin
// Onboard directly A6 and A7 are free, only PCB slot is taken (atm microswitches are connected)
// MCU to input SN74141N_0 pinout
#define A1 3  // LSB
#define B1 4
#define C1 5
#define D1 6  // MSB
// MCU to input SN74141N_1 pinout
#define A2 7  // LSB
#define B2 8
#define C2 9
#define D2 10  // MSB
// MCU to input SN74141N_2 pinout
#define A3 11  // LSB
#define B3 12
#define C3 13
#define D3 14 // A0, MSB
// MCU to input SN74141N_3 pinout
#define A4 15 // A1, LSB
#define B4 16 // A2
#define C4 0  // PCB A6 is wired with D0 (RX) (A6 can't be set as output directly)
#define D4 1  // PCB A7 is wired with D 1 (TX) (A7 can't be set as output directly), MSB
// MCU to microswitch pinout
#define switch_A3 A3 // A3, Edit Mode; Next digit.
#define switch_A6 A6 // Onboard A6, Digit down
#define switch_A7 A7 // Onboard A7, Digit up


// Arduino onboard pinout
int m_Arduino_Pinout[16] = {A1, B1, C1, D1,
                            A2, B2, C2, D2,
                            A3, B3, C3, D3,
                            A4, B4, C4, D4
                           };

// Arduino onboard defined and stored SN74141N_x pinouts
int m_SN74141N_Input_Pins_0[4] = {A1, B1, C1, D1};  // m_SN74141N_0 => hour digit_0
int m_SN74141N_Input_Pins_1[4] = {A2, B2, C2, D2};  // m_SN74141N_1 => hour digit_1
int m_SN74141N_Input_Pins_2[4] = {A3, B3, C3, D3};  // m_SN74141N_2 => minute digit_0
int m_SN74141N_Input_Pins_3[4] = {A4, B4, C4, D4};  // m_SN74141N_3 => minute digit_1
int *m_SN74141N_Drivers[4] = {m_SN74141N_Input_Pins_0, m_SN74141N_Input_Pins_1, m_SN74141N_Input_Pins_2, m_SN74141N_Input_Pins_3};

// Defined and stored  SN74141N input logic states
uint8_t m_A_Input_Logic_State;
uint8_t m_B_Input_Logic_State;
uint8_t m_C_Input_Logic_State;
uint8_t m_D_Input_Logic_State;
uint8_t m_SN74141N_Input_Logic_States[] = {m_A_Input_Logic_State, m_B_Input_Logic_State, m_C_Input_Logic_State, m_D_Input_Logic_State};

// Defined and stored calculated time
int m_hour_0; // MSB hour digit
int m_hour_1; // hour digit
int m_minute_0; // minute digit
int m_minute_1; // LSB minute digit
int m_Calculated_Time[] = {m_hour_0, m_hour_1, m_minute_0, m_minute_1}; // OGARNĄĆ DLACZEGO WARTOSCI W TABVLICY I OSOBNO SĄ INNE!!!!!

uint8_t hour;
uint8_t minute;
uint8_t second;

RTCDateTime dt;
DS3231 clock;

void setup()
{
  InitializePinouts();
  ClockTest();
  clock.begin();
  clock.setDateTime(0, 0, 0, 0, 0, 0); // year, month, day, hour, minute, second
}

void loop()
{
  CheckForMicroswitchPress();
  CalculateTime();
  for (int i = 0; i < 4; i++)
  {
    WriteValueOnTube(m_SN74141N_Drivers[i], m_Calculated_Time[i]);
  }
  delay(1000);
}

/*
    Defined functions by programmer are listed below
*/

// Assign real time using RTC library and store it in array
void CalculateTime()
{
  dt = clock.getDateTime();
  hour = dt.hour;
  minute = dt.minute;
  second = dt.second;

  m_Calculated_Time[0] = (hour / 10) % 10;
  m_Calculated_Time[1] = hour % 10;
  m_Calculated_Time[2] = (minute / 10) % 10;
  m_Calculated_Time[3] = minute % 10;

  //  m_Calculated_Time[0] = (minute / 10) % 10;
  //  m_Calculated_Time[1] = minute % 10;
  //  m_Calculated_Time[2] = (second / 10) % 10;
  //  m_Calculated_Time[3] = second % 10;
}

// Write value on one specific tube, assign logic state to arduino pinout, which are inputs of SN74141N
void WriteValueOnTube(int SN74141N_Driver_Input_Pins[4], uint8_t timeValue)
{
  SetLogicStates(timeValue);
  digitalWrite(SN74141N_Driver_Input_Pins[3], m_SN74141N_Input_Logic_States[3]); // Input Pin D, MSB
  digitalWrite(SN74141N_Driver_Input_Pins[2], m_SN74141N_Input_Logic_States[2]);
  digitalWrite(SN74141N_Driver_Input_Pins[1], m_SN74141N_Input_Logic_States[1]);
  digitalWrite(SN74141N_Driver_Input_Pins[0], m_SN74141N_Input_Logic_States[0]); // Input Pin A, LSB
}

// Set 0 or 1 in array of logic states based on given number, which represents input of SN74141N
void SetLogicStates(uint8_t timeValue)
{
  switch (timeValue)
  {
    case 0x00: // 0
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 0;
      break;
    case 0x01:  // 1 => 9  (decimal 1 |0001| is written as 9 |1001| on SN74141N input, but it still shows 1 ON Tube due to reversed Nixie Tube pinout order on PCB)
      m_SN74141N_Input_Logic_States[3] = 1; // Input Pin D, MSB ??
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 1; // Input Pin A, LSB ??
      break;
    case 0x02:  // 2 => 8
      m_SN74141N_Input_Logic_States[3] = 1;
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 0;
      break;
    case 0x03: // 3 => 7
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 1;
      m_SN74141N_Input_Logic_States[1] = 1;
      m_SN74141N_Input_Logic_States[0] = 1;
      break;
    case 0x04: // 4 => 6
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 1;
      m_SN74141N_Input_Logic_States[1] = 1;
      m_SN74141N_Input_Logic_States[0] = 0;
      break;
    case 0x05: // 5 => 5
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 1;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 1;
      break;
    case 0x06: // 6 => 4
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 1;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 0;
      break;
    case 0x07: // 7 => 3
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 1;
      m_SN74141N_Input_Logic_States[0] = 1;
      break;
    case 0x08: // 8 => 2
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 1;
      m_SN74141N_Input_Logic_States[0] = 0;
      break;
    case 0x09: // 9 => 1
      m_SN74141N_Input_Logic_States[3] = 0;
      m_SN74141N_Input_Logic_States[2] = 0;
      m_SN74141N_Input_Logic_States[1] = 0;
      m_SN74141N_Input_Logic_States[0] = 1;
      break;
  }
}

// Check if A3 switch is pressed (LOW state)
void CheckForMicroswitchPress()
{
  int currentTubeDriver = 0;
  int pressedTime = 0;

  // if switch_A3 is pressed then enter statement
  if (analogRead(switch_A3) == LOW)
  {
    BlinkOnAndOff(4);
    while (true)
    {
      EditModeBlinkOnAndOff(currentTubeDriver);

      // if switch_A6 is pressed, then substract number on tube, or change number if out of range
      if (analogRead(switch_A6) == LOW)
      {
        TimeFormatLogic(currentTubeDriver, false);
        WriteValueOnTube(m_SN74141N_Drivers[currentTubeDriver], m_Calculated_Time[currentTubeDriver]);
      }

      // if switch_A7 is pressed, then add number on tube, or change number if out of range
      else if (analogRead(switch_A7) == LOW)
      {
        TimeFormatLogic(currentTubeDriver, true);
        WriteValueOnTube(m_SN74141N_Drivers[currentTubeDriver], m_Calculated_Time[currentTubeDriver]);
      }

      // if switch_A3 is pressed, then change on next one, or set current time after 1 second press and exit function
      if (analogRead(switch_A3) == LOW)
      {
        while (analogRead(switch_A3) == LOW)
        {
          delay(100);   // zamiast delay ogarnac to z millis()
          pressedTime += 100;
          if (pressedTime > 1000)
          {
            clock.setDateTime(0, 0, 0, ((m_Calculated_Time[0] * 10) + m_Calculated_Time[1]), ((m_Calculated_Time[2] * 10) + m_Calculated_Time[3]), 0);
            BlinkOnAndOff(2);
            return false;
          }
        }
        currentTubeDriver += 1;
        pressedTime = 0;
        if (currentTubeDriver > 3)
        {
          currentTubeDriver = 0;
        }
      }
    }
  }
}

// Check for proper time settins, eg. user can't set 25:00 beacause maximum value is 23:59.
void TimeFormatLogic(int currentTubeDriver, bool mathematicalOperatorState)
{
  switch (currentTubeDriver)
  {
    case 0:
      if (mathematicalOperatorState == true)
      {
        if (m_Calculated_Time[0] >= 2)
        {
          m_Calculated_Time[0] = 0;
        }
        else if (m_Calculated_Time[1] >= 4 && m_Calculated_Time[0] == 1)
        {
          break;
        }
        else {
          m_Calculated_Time[0] += 1;
        }
      }
      else if (mathematicalOperatorState == false)
      {
        if (m_Calculated_Time[1] >= 4 && m_Calculated_Time[0] == 0)
        {
          break;
        }
        if (m_Calculated_Time[0] <= 0)
        {
          m_Calculated_Time[0] = 2;
        }
        else {
          m_Calculated_Time[0] -= 1;
        }
      }
      break;
    case 1:
      if (mathematicalOperatorState == true)
      {
        if (m_Calculated_Time[0] >= 2)
        {
          if (m_Calculated_Time[1] >= 3)
          {
            m_Calculated_Time[1] = 0;
          }
          else
          {
            m_Calculated_Time[1] += 1;
          }
        }
        else if (m_Calculated_Time[1] >= 9)
        {
          m_Calculated_Time[1] = 0;
        }
        else {
          m_Calculated_Time[1] += 1;
        }
      }
      else if (mathematicalOperatorState == false)
      {
        if (m_Calculated_Time[0] >= 2)
        {
          if (m_Calculated_Time[1] <= 0)
          {
            m_Calculated_Time[1] = 3;
          }
          else
          {
            m_Calculated_Time[1] -= 1;
          }
        }
        else if (m_Calculated_Time[1] <= 0)
        {
          m_Calculated_Time[1] = 9;
        }
        else {
          m_Calculated_Time[1] -= 1;
        }
      }
      break;
    case 2:
      if (mathematicalOperatorState == true)
      {
        if (m_Calculated_Time[2] >= 5)
        {
          m_Calculated_Time[2] = 0;
        }
        else
        {
          m_Calculated_Time[2] += 1;
        }
      }
      else if (mathematicalOperatorState == false)
      {
        if (m_Calculated_Time[2] <= 0)
        {
          m_Calculated_Time[2] = 5;
        }
        else
        {
          m_Calculated_Time[2] -= 1;
        }
      }
      break;
    case 3:
      if (mathematicalOperatorState == true)
      {
        if (m_Calculated_Time[3] >= 9)
        {
          m_Calculated_Time[3] = 0;
        }
        else
        {
          m_Calculated_Time[3] += 1;
        }
      }
      else if (mathematicalOperatorState == false)
      {
        if (m_Calculated_Time[3] <= 0)
        {
          m_Calculated_Time[3] = 9;
        }
        else
        {
          m_Calculated_Time[3] -= 1;
        }
      }
      break;
    default:
      break;
  }
}

// Turn on and off tubes with changes on SN74141N logic states
void BlinkOnAndOff(int t)
{
  for (int i = 0; i < t; i++)
  {
    TurnOffAllTubes();
    delay(100);
    for (int i = 0; i < 4; i++)
    {
      WriteValueOnTube(m_SN74141N_Drivers[i], m_Calculated_Time[i]);
    }
    delay(100);
  }
}

// Turn on and off tubes with changes on SN74141N logic states, but specific tube is ommited
void EditModeBlinkOnAndOff(int currentTubeDriver)
{
  for (int i = 0; i < 4; i++)
  {
    if (i == currentTubeDriver)
    {
      continue;
    }
    TurnOffTubeByID(i);
  }
  delay(500);
  for (int i = 0; i < 4; i++)
  {
    if (i == currentTubeDriver)
    {
      continue;
    }
    WriteValueOnTube(m_SN74141N_Drivers[i], m_Calculated_Time[i]);
  }
  delay(500);
}

// Initialize Arduino pinouts
void InitializePinouts()
{
  pinMode(A3, INPUT);
  for (int i = 0; i < 16; i++)
  {
    pinMode(m_Arduino_Pinout[i], OUTPUT);
  }
}

// Turn off all SN74141N drivers
void TurnOffAllTubes()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(m_Arduino_Pinout[i], 1);
  }
}

// Turn off tube by SN74141N ID
void TurnOffTubeByID(int ID)
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(m_SN74141N_Drivers[ID][i], 1);
  }
}

/*
    Used for debugging
*/

void ClockTest()
{
  for (int i = 0; i < 10; i++)
  {
    WriteValueOnTube(m_SN74141N_Drivers[0], i);
    WriteValueOnTube(m_SN74141N_Drivers[1], i);
    WriteValueOnTube(m_SN74141N_Drivers[2], i);
    WriteValueOnTube(m_SN74141N_Drivers[3], i);
    delay(200);
  }
  TurnOffAllTubes();
}

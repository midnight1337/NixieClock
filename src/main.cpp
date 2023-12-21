/*
Title: Nixie Clock
Author: midnight1337
Description: Nixie tube clock in HH:MM format
Date: 18-12-2023
*/

/*
TODO:
1.Time format logic for each digit
2.Use onebutton lib in event() method
*/

#include "../include/manager.h"


int main()
{
  init();
  // Serial.begin(115200);

  Manager manager{};

  while (true)
  {
    manager.run();
    delay(1000);
  }
}

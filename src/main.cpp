/*
Title: Nixie Clock
Author: midnight1337
Description: Nixie tube clock in HH:MM format
Date: 18-12-2023
*/

/*
TODO:
1.Time format logic for each digit in progress
1a.Maybe make it not for each digit but just for HH:MM format??
1b.manager::event() method in progress
2.Use onebutton lib in event() method
3.Current driver in edit mode is blinking
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

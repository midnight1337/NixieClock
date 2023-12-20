/*
Title: Nixie Clock
Author: midnight1337
Date: 18-12-2023
*/
/*
TODO:
1.RTC libraries and functionality
2.Time format logic for each digit
3.Store in table current time digit for each driver
*/
#include "manager.h"


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

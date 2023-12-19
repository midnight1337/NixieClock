/*
Title: Nixie Clock
Author: midnight1337
Date: 18-12-2023
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

/*
Title: Nixie Clock
Author: midnight1337
Date: 2023 - 12 - 18
*/
#include <Arduino.h>
#include "manager.h"


int main()
{
  init();
  // Serial.begin(115200);

  Manager manager{};

  while (true)
  {
    manager.run();
  }
}

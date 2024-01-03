/*
Title: Nixie Clock
Author: midnight1337
Description: Nixie tube clock
Date: 18-12-2023
*/

/*
TODO:
-manager::event() method in progress - Use onebutton lib in event() method, actual switch instructions are wrong
*/
#include "../include/manager.h"


int main()
{
  init();
  // Serial.begin(115200);

  Manager manager{};
  manager.setup();
  manager.run_tubes_test();

  while (true)
  {
    manager.run();
    delay(1000);
  }
}

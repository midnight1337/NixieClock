/*
Title: Nixie Clock
Author: midnight1337
Description: Nixie tube clock in HH:MM format
Date: 18-12-2023
*/

/*
TODO:
1.Time format logic for each digit - change it according to drivers group
2.manager::event() method in progress - Use onebutton lib in event() method
3.manager::blinking_tubes - do it according to drivers group??
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

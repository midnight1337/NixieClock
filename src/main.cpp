/**
 * @title: Nixie Clock
 * @author midnight1337
 * @brief A class-organised program, designed for running Clock based on Nixie Tubes.
 * @date: 18-12-2023
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

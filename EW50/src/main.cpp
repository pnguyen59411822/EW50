#include <Arduino.h>

#include "Logger.h"
#include "hcsr04.h"


Logger Log(true);


void setup() {
  HCSR04_setup();
}

void loop() {
  HCSR04_read();
}

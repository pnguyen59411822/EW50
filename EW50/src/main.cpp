#include <Arduino.h>

#include "Logger.h"
#include "hcsr04.h"


Logger Log(true);


void setup() {
  HCSR04_init();
}

void loop() {
  HCSR04_read();
}

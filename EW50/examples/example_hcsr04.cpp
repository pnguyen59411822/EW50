#include <Arduino.h>

#include "hcsr04.h"


void setup() {
  Serial.begin(9600);
  HCSR04_setup();
}

void loop() {
  HCSR04_read();
}

#include <Arduino.h>

#include "Logger.h"
#include "hcsr04.h"
#include "voltage.h"
#include "acs712_sensor.h"


Logger Log(true);


void setup() {
  HCSR04_init();
}

void loop() {
  HCSR04_read();
  Voltage_read();

  Log.inf("[ACS712] current DC: %d", ACS712_getCurrentDC());
}

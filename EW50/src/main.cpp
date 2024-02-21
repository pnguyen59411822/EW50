#include <Arduino.h>

#include "Logger.h"
#include "hcsr04.h"
#include "voltage.h"
#include "acs712_sensor.h"
#include "flow_rate.h"


Logger Log(true);


void setup() {
  HCSR04_init();
  FlowRate_init();
}

void loop() {
  HCSR04_read();
  Voltage_read();
  FlowRate_read();

  Log.inf("[Voltage] Solar: %.2f", Voltage_getSolar());
  Log.inf("[Voltage] Water: %.2f", Voltage_getWater());
  Log.inf("[ACS712] current DC: %d", ACS712_getSolar());
}

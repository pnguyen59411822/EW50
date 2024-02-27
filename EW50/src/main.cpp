#include <Arduino.h>

#include "Logger.h"
#include "uart_service.h"
#include "hcsr04.h"
#include "voltage.h"
#include "acs712_sensor.h"
#include "flow_sensor.h"


Logger Log(true);


void setup() {
  Log.init();
  UART_init();
  HCSR04_init();
  FlowSensor_init();
}

void loop() {
  HCSR04_read();
  Voltage_read();
  FlowSensor_read();
  UART_loop();

  Log.inf("[Voltage] Solar: %.2f", Voltage_getSolar());
  Log.inf("[Voltage] Water: %.2f", Voltage_getWater());
  Log.inf("[ACS712] current DC: %d", ACS712_getSolar());
}

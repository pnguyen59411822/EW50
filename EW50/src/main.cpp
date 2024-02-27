#include <Arduino.h>

#include "Logger.h"
#include "uart_service.h"
#include "hcsr04.h"
#include "voltage.h"
#include "acs712_sensor.h"
#include "flow_sensor.h"


Logger Log(true);

#define FLOAT_LENGTH_MIN 7
#define FLOAT_NUM_DIGIT  2

char str_i[FLOAT_LENGTH_MIN];

char* get_cstr(float f){
  dtostrf(f, FLOAT_LENGTH_MIN, FLOAT_NUM_DIGIT, str_i);
  return str_i;
}


void setup() {
  Log.init();
  UART_init();
  HCSR04_init();
  ACS712_calibrate();
  FlowSensor_init();
}

void loop() {

  HCSR04_read();
  Voltage_read();
  FlowSensor_read();
  UART_loop();

  // Log.inf("[Voltage] Solar: %s", get_cstr(Voltage_getSolar()));
  // Log.inf("[Voltage] Water: %s", get_cstr(Voltage_getWater()));
  // Log.inf("[ACS712] current DC: %s", get_cstr(ACS712_getSolar()));
}

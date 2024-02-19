#include <Arduino.h>

#include "Logger.h"
#include "uart_service.h"
#include "hcsr04.h"


Logger Log(true);


void setup() {
  UART_init();
  HCSR04_setup();
}

void loop() {
  HCSR04_read();
  UART_loop();
}

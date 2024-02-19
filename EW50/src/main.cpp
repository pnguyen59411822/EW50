#include <Arduino.h>

#include "Logger.h"
#include "wifi_service.h"
#include "uart_service.h"

static Logger Log(true);


void setup() {
  // Wait for Serial beginning
  delay(500);
  UART_init();
  WiFi_init();
}

void loop() {
  UART_loop();
}

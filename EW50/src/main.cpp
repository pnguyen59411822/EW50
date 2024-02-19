#include <Arduino.h>

#include "Logger.h"
#include "wifi_service.h"
#include "uart_service.h"
#include "firebase_service.h"

static Logger Log(true);


void setup() {
  // Wait for Serial beginning
  delay(500);
  UART_init();
  WiFi_init();
  Firebase_init();
}

void loop() {
  Firebase_loop();  
  UART_loop();
}

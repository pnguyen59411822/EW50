#include <Arduino.h>

#include "Logger.h"
#include "wifi_service.h"
#include "firebase_service.h"

static Logger Log(true);


void setup() {
  // Wait for Serial beginning
  delay(500);
  WiFi_init();
  Firebase_init();
}

void loop() {
  Firebase_loop();
}

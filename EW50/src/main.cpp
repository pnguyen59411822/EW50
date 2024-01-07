#include <Arduino.h>

#include "Logger.h"

Logger Log1, Log2;

void my_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[100];
    int written = vsprintf(buffer, fmt, args);

    Serial.write(buffer, written);
    Serial.printf("");

    va_end(args);
}


void setup() {
  // Wait for Serial beginning
  delay(500);
  
}

void loop() {

}

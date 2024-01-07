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

  my_printf("[%s] %d success\n\n", "test", 99);

  Serial.println("[Serial] success");
  Serial.printf("[Serial] %s success\n\n", "printf");

  delay(1000);  Log1.inf("[1] Info success");
  delay(1000);  Log1.upd("[1] Update success");
  delay(1000);  Log1.err("[1] Error success");
  delay(1000);  Log1.printf("[1] %s success\n", "printf");
  delay(1000);  Log1.print("[1] print success\n\n");

  delay(1000);  Log2.inf("[2] Info success");
  delay(1000);  Log2.upd("[2] Update success");
  delay(1000);  Log2.err("[2] Error success");
  delay(1000);  Log2.printf("[2] %s success\n", "printf");
  delay(1000);  Log2.print("[2] print success\n\n");
}

void loop() {

}

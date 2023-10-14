#include "unity.h"
#include "Arduino.h"


void setUp() {
    //
}


void tearDown() {
    //
}


void test_serial_print() {
  // open pio terminal, use "pio test -v" to see Serial's output
  Serial.println("Serial print successfully");
}


int runUnityTests() {
  UNITY_BEGIN();
  RUN_TEST(test_serial_print);
  return UNITY_END();
}


void setup() {
    Serial.begin(9600);

    // Wait for test runner
    delay(2000);

    runUnityTests();
}


void loop() {

}
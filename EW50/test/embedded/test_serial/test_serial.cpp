#include "unity.h"
#include "Arduino.h"


/* ==================================================
** Function Declarations
**
** =============================================== */


int runUnityTests();

void test_serial_print();



/* ==================================================
** Core functions
**
** =============================================== */



void setUp() {
    //
}


void tearDown() {
    //
}


void setup() {
    Serial.begin(115200);

    // wait for test runner
    delay(2000);

    runUnityTests();
    delay(2000);
}


void loop() {
    
}



/* ==================================================
** Function definitions
**
** =============================================== */



int runUnityTests() {
    UNITY_BEGIN();
    RUN_TEST(test_serial_print);
    return UNITY_END();
}


void test_serial_print() {
    Serial.print("Serial print successfully\n");
}
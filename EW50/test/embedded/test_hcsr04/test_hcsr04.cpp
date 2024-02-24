#include <unity.h>

#include "hcsr04.h"
#include "hcsr04.const.h"


int runUnitTests();
void test_pinEcho();
void test_pinTrig();


void setUp() {
    //
}


void tearDown() {
    //
}


void setup() {
    
    // wait for test runner
    delay(2000);

    HCSR04_setup();
    runUnitTests();
}


void loop() {

}


int runUnitTests() {
    UNITY_BEGIN();
    RUN_TEST(test_pinTrig);
    RUN_TEST(test_pinEcho);
    return UNITY_END();
}


void test_pinEcho() {

    int expected = HIGH;
    int actual   = digitalRead(PINS.ECHO);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, "Please set pinMode is INPUT");
}


void test_pinTrig() {

    int expected = HIGH;
    int actual   = HIGH;

    digitalWrite(PINS.TRIG, expected);
    actual = digitalRead(PINS.TRIG);
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, "Please check power of trig pin");

    expected = LOW;
    digitalWrite(PINS.TRIG, expected);
    actual = digitalRead(PINS.TRIG);
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, "Please set pinMode is OUTPUT");
}
/* ==================================================
** Libraries
**
** =============================================== */


#include "hcsr04.h"
#include "hcsr04.const.h"



/* ==================================================
** Macro definition
**
** =============================================== */


// #define ENABLE_DEBUG


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


//


/* ==================================================
** Static variables
**
** =============================================== */


double distance_cm = 0.0;


/* ==================================================
** Static function declaration
**
** =============================================== */


void send_pulse();
void calc_distance();


/* ==================================================
** Static function definition
**
** =============================================== */


void send_pulse() {

    digitalWrite(PINS.TRIG, LOW);  
	delayMicroseconds(2);  

	digitalWrite(PINS.TRIG, HIGH);  
	delayMicroseconds(10);  
    
	digitalWrite(PINS.TRIG, LOW);  

}


void calc_distance() {

    unsigned long duration = pulseIn(PINS.ECHO, HIGH);
    const double speed_cm_per_microsecond = 0.0343;

    distance_cm = (duration*speed_cm_per_microsecond) / 2;
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void HCSR04_setup() {

	pinMode(PINS.TRIG, OUTPUT);  
	pinMode(PINS.ECHO, INPUT);

}


void HCSR04_read() {

    const uint32_t TIME = 100;
    static uint32_t intv = millis();

    if(millis() - intv < TIME) {
        return;
    }

    send_pulse();
    calc_distance();

    #ifdef ENABLE_DEBUG
    Serial.print("Distance: ");
    Serial.print(HCSR04_get_cm());
    Serial.print(" cm");
    Serial.println();
    #endif

    intv = millis();
}


float HCSR04_get_m() {
    return (float) (distance_cm / 100);
}


float HCSR04_get_cm() {
    return (float) distance_cm;
}
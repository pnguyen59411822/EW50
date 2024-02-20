/* ==================================================
** Libraries
**
** =============================================== */


#include "voltage.h"
#include "voltage.const.h"

#include "pin_table.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


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


static float volt_src = 0;


/* ==================================================
** Static function declaration
**
** =============================================== */


//


/* ==================================================
** Static function definition
**
** =============================================== */


//


/* ==================================================
** Extern function definition
**
** =============================================== */


void Voltage_read() {

    static uint32_t intv = millis();

    if(millis() - intv < 500) {
        return;
    }

    intv = millis();

    uint16_t adc_r2  = analogRead(VOLTAGE_SENSOR_PIN_SOLAR);
    float    volt_r2 = (float)(adc_r2 * VOLTAGE_REF) / ADC_RESOLUTION;
    
    volt_src  = volt_r2 * (RESISTOR_1 + RESISTOR_2) / RESISTOR_2; 
}


float Voltage_get() {
    return volt_src;
}
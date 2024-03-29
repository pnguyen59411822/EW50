/* ==================================================
** Libraries
**
** =============================================== */


#include "voltage.h"
#include "voltage.const.h"
#include <SimpleKalmanFilter.h>

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


static SimpleKalmanFilter fillter(1, 5, 0.05);
static float volt_solar = 0;
static float volt_water = 0;


/* ==================================================
** Static function declaration
**
** =============================================== */


static void read_solarVolt();
static void read_waterVolt();


/* ==================================================
** Static function definition
**
** =============================================== */


void read_solarVolt(){

    uint16_t adc_r2  = analogRead(VOLTAGE_SENSOR_PIN_SOLAR);
             adc_r2  = fillter.updateEstimate(adc_r2);
    float    volt_r2 = (float)(adc_r2 * VOLTAGE_REF) / ADC_RESOLUTION;
    
    volt_solar  = volt_r2 * (RESISTOR_1 + RESISTOR_2) / RESISTOR_2; 
}


void read_waterVolt(){

    uint16_t adc_r2  = analogRead(VOLTAGE_SENSOR_PIN_WATER);
             adc_r2  = fillter.updateEstimate(adc_r2);
    float    volt_r2 = (float)(adc_r2 * VOLTAGE_REF) / ADC_RESOLUTION;
    
    volt_water  = volt_r2 * (RESISTOR_1 + RESISTOR_2) / RESISTOR_2; 
}


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

    read_solarVolt();
    read_waterVolt();
}


float Voltage_getSolar() {
    return volt_solar;
}


float Voltage_getWater() {
    return volt_water;
}
/* ==================================================
** Libraries
**
** =============================================== */


#include "flow_sensor.h"
#include "flow_sensor.const.h"

#include "pin_table.h"
#include "Logger.h"


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


static Logger Log(true);

static volatile byte pulseCount = 0;

// Litres / minute
static float flowRate = 0;
// MilliLitres in a measure
static uint16_t flowMilliLitres = 0;
static uint32_t totalMilliLitres = 0;


/* ==================================================
** Static function declaration
**
** =============================================== */


static void pulseCounter();


/* ==================================================
** Static function definition
**
** =============================================== */


void pulseCounter(){
    pulseCount += 1;
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void FlowSensor_init(){
    pinMode(FLOW_SENSOR_PIN, INPUT);
    digitalWrite(FLOW_SENSOR_PIN, HIGH);

    attachInterrupt(FLOW_SENSOR_PIN, pulseCounter, FALLING);
}


void FlowSensor_read(){
    static uint32_t millis_prev = 0;
    const float     TIMEOUT     = 1000.0;
    const uint32_t  intv        = millis() - millis_prev;

    if(intv < TIMEOUT){
        return;
    }

    millis_prev = millis();

    // FLOW_SENSOR_PIN is 2
    detachInterrupt(FLOW_SENSOR_PIN_INTERRUPT);

    flowRate          = ((TIMEOUT / intv) * pulseCount) / FLOW_SENSOR_FACTOR_CALIBRATE;
    flowMilliLitres   = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    pulseCount = 0;
    attachInterrupt(FLOW_SENSOR_PIN_INTERRUPT, pulseCounter, FALLING);

    Log.print("\n");
    Log.inf("[flow_sensor] rate (L/min):                %.2f", flowRate);
    Log.inf("[flow_sensor] Output Liquid Quantity (mL): %lu", totalMilliLitres);
    Log.print("\n");
}


// Litres / minute
float FlowSensor_get_rate(){
    return flowRate;
}


uint32_t FlowSensor_get_totalMilliLitres(){
    return totalMilliLitres;
}
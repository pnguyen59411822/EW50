/* ==================================================
** Libraries
**
** =============================================== */


#include "flow_rate.h"
#include "flow_rate.const.h"

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


void FlowRate_init(){
    pinMode(FLOW_RATE_SENSOR_PIN, INPUT);
    digitalWrite(FLOW_RATE_SENSOR_PIN, HIGH);

    attachInterrupt(FLOW_RATE_SENSOR_PIN, pulseCounter, FALLING);
}


void FlowRate_read(){
    static uint32_t millis_prev = 0;
    const float     TIMEOUT     = 1000.0;
    const uint32_t  intv        = millis() - millis_prev;

    if(intv < TIMEOUT){
        return;
    }

    millis_prev = millis();

    // FLOW_RATE_SENSOR_PIN is 2
    detachInterrupt(INTERRUPT_PIN_2);

    flowRate          = ((TIMEOUT / intv) * pulseCount) / FLOW_RATE_FACTOR_CALIBRATE;
    flowMilliLitres   = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    pulseCount = 0;
    attachInterrupt(INTERRUPT_PIN_2, pulseCounter, FALLING);

    Log.print("\n");
    Log.inf("[flow_rate] rate (L/min):                %.2f", flowRate);
    Log.inf("[flow_rate] Output Liquid Quantity (mL): %lu", totalMilliLitres);
    Log.print("\n");
}
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

static float flowRate = 0;
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


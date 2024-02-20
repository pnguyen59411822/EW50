/* ==================================================
** Libraries
**
** =============================================== */


#include "acs712_sensor.h"
#include "acs712_sensor.const.h"

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
static ACS712 sensor(ACS712_TYPE, ACS712_PIN);

static uint16_t current_dc = 0;
static uint32_t intv_lastMeasure = millis();


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


// calibrate() method calibrates zero point of sensor,
// It is not necessary, but may positively affect the accuracy
// Ensure that no current flows through the sensor at this moment
// If you are not sure that the current through the sensor will not leak during calibration - comment out this method
void ACS712_calibrate(){

    Log.print("\n");
    Log.inf("[ACS712] Calibrating... ");
    Log.inf("[ACS712] Ensure that no current flows through the sensor at this moment");

    int zero = sensor.calibrate();

    Log.inf("[ACS712] Done!");
    Log.inf("Zero point for this sensor = %d", zero);
    Log.print("\n");
}


float ACS712_getCurrentDC(){

    if(millis() - intv_lastMeasure >= 1000) {
        current_dc = sensor.getCurrentDC();
        intv_lastMeasure = millis();
    }
    
    return current_dc;
}

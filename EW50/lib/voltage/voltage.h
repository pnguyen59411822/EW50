#ifndef voltage_h
#define voltage_h


/* ==================================================
** Libraries
**
** =============================================== */


#include <Arduino.h>


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
** Extern function declaration
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


void  Voltage_read();
float Voltage_getSolar();
float Voltage_getSolarLoad();
float Voltage_getWater();
float Voltage_getWaterLoad();


#endif
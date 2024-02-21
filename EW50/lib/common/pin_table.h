#ifndef pin_table_h
#define pin_table_h


/* ==================================================
** Libraries
**
** =============================================== */


#include <Arduino.h>


/* ==================================================
** Macro definition
**
** =============================================== */


#define INTERRUPT_PIN_2             0
#define INTERRUPT_PIN_3             1
#define INTERRUPT_PIN_21            2
#define INTERRUPT_PIN_20            3
#define INTERRUPT_PIN_19            4
#define INTERRUPT_PIN_18            5

#define PIN_TX1                     18
#define PIN_RX1                     19
#define PIN_TX2                     16
#define PIN_RX2                     17
#define PIN_TX3                     14
#define PIN_RX3                     15


#define VOLTAGE_SENSOR_PIN_SOLAR    A0
#define VOLTAGE_SENSOR_PIN_WATER    A7

#define ACS712_PIN_SOLAR            A3

#define FLOW_RATE_SENSOR_PIN            2
#define FLOW_RATE_SENSOR_PIN_INTERRUPT INTERRUPT_PIN_2

#define HUB_TX  PIN_RX1
#define HUB_RX  PIN_TX1


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


//


#endif
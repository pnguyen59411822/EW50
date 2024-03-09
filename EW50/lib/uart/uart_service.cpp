/* ==================================================
** Libraries
**
** =============================================== */


#include "uart_service.deps.h"
#include "uart_service.const.h"
#include "uart_service.h"
#include "common.h"

#include "Logger.h"
#include "voltage.h"
#include "voltage.const.h"
#include "acs712_sensor.h"
#include "flow_sensor.h"


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
static SoftwareSerial mySerial(UART_RX_DEFAULT, UART_TX_DEFAULT);


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


void UART_init() {
    mySerial.begin(UART_BAUND_RATE_DEFAULT);
    while(!mySerial);
    Log.inf("[UART] init... success");
}


void UART_loop() {
  const uint64_t  TIMEOUT     = 1500;
  static uint64_t millis_prev = millis();
  const uint64_t  intv        = millis() - millis_prev;

  if(intv < TIMEOUT){
    return;
  }

  millis_prev = millis();

  float volt_solar      = Voltage_getSolar();
  float volt_solarLoad  = Voltage_getSolarLoad();
  float ampe_solarLoad  = ACS712_getSolar();
  float power_solarLoad = volt_solarLoad * ampe_solarLoad;

  float volt_water      = Voltage_getWater();
  float volt_waterLoad  = Voltage_getWaterLoad();
  float ampe_waterLoad  = volt_water / RESISTOR_2;
  float power_waterLoad = volt_waterLoad * ampe_waterLoad;
  float flow_rate       = FlowSensor_get_rate();
  
  uint32_t totalMilliLitres = FlowSensor_get_totalMilliLitres();


  String data = String(volt_solar, 2)      + "," +
                String(volt_solarLoad, 2)  + "," +
                String(ampe_solarLoad, 2)  + "," +
                String(power_solarLoad, 2) + "," +
                String(volt_water, 2)      + "," +
                String(volt_waterLoad, 2)  + "," +
                String(ampe_waterLoad, 2)  + "," +
                String(power_waterLoad, 2) + "," +
                String(flow_rate, 2)       + "," +
                String(totalMilliLitres)
                ;

  Log.inf("[UART] sent data: %s", data.c_str());
  mySerial.print(data);
}
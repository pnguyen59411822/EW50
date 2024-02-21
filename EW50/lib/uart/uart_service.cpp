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
#include "flow_rate.h"


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


// static String getValue(String data, char separator, int index);


/* ==================================================
** Static function definition
**
** =============================================== */

/*
String getValue(String data, char separator, unsigned int index) {
  int found = 0;
  int startIndex = 0;
  int endIndex = -1;
  int maxIndex = data.length() - 1;
  
  // Trả về chuỗi rỗng nếu index lớn hơn hoặc bằng số lượng phần tử
  if (index >= maxIndex) {
    return ""; 
  }

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    // Nếu tìm thấy ký tự phân tách thì trả về một đoạn
    // Nếu không tìm thấy ký tự phân tách thì trả về toàn bộ
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      startIndex = endIndex + 1;
      endIndex = (i == maxIndex) ? i + 1 : i;
    }
  }

  if (found > index) {
    return data.substring(startIndex, endIndex);
  }

  // Không nên đến đây (lỗi logic nếu thực hiện đúng vòng lặp)
  return "";
}
/**/


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
  const uint64_t  TIMEOUT     = 1000;
  static uint64_t millis_prev = millis();
  const uint64_t  intv        = millis() - millis_prev;

  if(intv < TIMEOUT){
    return;
  }

  millis_prev = millis();

  float volt_solar  = Voltage_getSolar();
  float ampe_solar  = ACS712_getSolar();
  float power_solar = volt_solar * ampe_solar;

  float volt_water  = Voltage_getWater();
  float ampe_water  = volt_water / RESISTOR_2;
  float power_water = volt_water * ampe_water;
  float flow_rate   = FlowRate_get_rate();
  
  uint32_t totalMilliLitres = FlowRate_get_totalMilliLitres();


  String data = String(volt_solar, 2)  + "," +
                String(ampe_solar, 2)  + "," +
                String(power_solar, 2) + "," +
                String(volt_water, 2)  + "," +
                String(ampe_water, 2)  + "," +
                String(power_water, 2) + "," +
                String(flow_rate, 2)   + "," +
                String(totalMilliLitres)
                ;

  Log.inf("[UART] sent data: %s", data.c_str());
  mySerial.print(data);
}
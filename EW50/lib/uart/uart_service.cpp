/* ==================================================
** Libraries
**
** =============================================== */


#include "uart_service.deps.h"
#include "uart_service.const.h"
#include "uart_service.h"
#include "common.h"

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
    if(mySerial.available()) {
        String uart_data = mySerial.readString();
        Log.inf("[UART] receive data: %s", uart_data.c_str());
    }
}
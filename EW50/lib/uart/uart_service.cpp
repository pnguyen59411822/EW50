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
    if(mySerial.available()) {
        uart_data = mySerial.readString();
        Log.inf("[UART] receive data: %s", uart_data.c_str());
    }
}
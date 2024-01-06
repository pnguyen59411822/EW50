#ifndef Logger_h
#define Logger_h


/* ==================================================
** Libraries
**
** =============================================== */


#include "Logger.const.h"


/* ==================================================
** Class declaration
**
** =============================================== */


class Logger;


/* ==================================================
** Class definition
**
** =============================================== */


class Logger
{
    // Constructor
    public: Logger(
        HardwareSerial *LOG_PORT=LOG_PORT_DEFAULT, 
        uint32_t MONITOR_SPEED=MONITOR_SPEED_DEFAULT,
        bool flg_enable=true
    );

    // Methods
    public: void print(const char *fmt);
    public: void printf(const char *fmt, ...);
    public: void inf(const char *fmt, ...);
    public: void err(const char *fmt, ...);
    public: void upd(const char *fmt, ...);

    // Attributes
    private: bool flg_upd;
    private: HardwareSerial *LOG_PORT;
    private: const uint32_t MONITOR_SPEED;
};


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif
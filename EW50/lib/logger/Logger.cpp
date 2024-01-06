/* ==================================================
** Libraries
**
** =============================================== */


#include "Logger.h"


/* ==================================================
** Logger: Constructors
**
** =============================================== */


Logger::Logger(
    HardwareSerial  *LOG_PORT, 
    uint32_t        MONITOR_SPEED,
    bool            flg_enable
)
    : LOG_PORT(LOG_PORT)
    , MONITOR_SPEED(MONITOR_SPEED)
{

    if (!flg_enable) {
        this->LOG_PORT = nullptr;
        return;
    }
    
    LOG_PORT->begin(MONITOR_SPEED);
    LOG_PORT->print("\n\n\r");
    delay(500);
}


/* ==================================================
** Logger: Methods
**
** =============================================== */


void Logger::print(const char *fmt) {
    if(LOG_PORT == nullptr) {
        return;
    }

    LOG_PORT->print(fmt);
}


void Logger::printf(const char *fmt, ...) {
    if(LOG_PORT == nullptr) {
        return;
    }

    // In thông tin ra serial
    va_list args;
    va_start(args, fmt);

    // In nội dung thông tin
    vprintf(fmt, args);
    
    // Dọn dẹp bộ nhớ
    va_end(args);
}


void Logger::inf(const char *fmt, ...) {
    if(LOG_PORT == nullptr) {
        return;
    }

    // Kiểm tra xem đã cập nhật chưa
    if (flg_upd) {
        // Cập nhật trạng thái
        flg_upd = false;

        // In xuống dòng
        LOG_PORT->println();
    }

    // In thông tin ra serial
    va_list args;
    va_start(args, fmt);

    // In thời gian
    LOG_PORT->printf("I (%.3Lf) ", (long double)millis() / 1000);

    // In nội dung thông tin
    vprintf(fmt, args);

    // In xuống dòng
    LOG_PORT->println();
    
    // Dọn dẹp bộ nhớ
    va_end(args);
}


void Logger::err(const char *fmt, ...) {
    if(LOG_PORT == nullptr) {
        return;
    }

    // Kiểm tra xem đã cập nhật chưa
    if (flg_upd) {
        // Cập nhật trạng thái
        flg_upd = false;

        // In xuống dòng
        LOG_PORT->println();
    }

    // In thông tin ra serial
    va_list args;
    va_start(args, fmt);

    // In thời gian
    LOG_PORT->printf("E (%.3Lf) ", (long double)millis() / 1000);

    // In nội dung thông tin
    vprintf(fmt, args);

    // In xuống dòng
    LOG_PORT->println();
    
    // Dọn dẹp bộ nhớ
    va_end(args);
}


void Logger::upd(const char *fmt, ...) {
    if(LOG_PORT == nullptr) {
        return;
    }

    flg_upd = true;

    // In thông tin ra serial
    va_list args;
    va_start(args, fmt);

    // In thời gian
    LOG_PORT->printf("U (%.3Lf) ", (long double)millis() / 1000);

    // In nội dung thông tin
    vprintf(fmt, args);

    // Con trỏ quay về đầu dòng
    LOG_PORT->print("\r");
    
    // Dọn dẹp bộ nhớ
    va_end(args);
}


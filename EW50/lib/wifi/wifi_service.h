#ifndef wifi_service_h
#define wifi_service_h


/* ==================================================
** Libraries
**
** =============================================== */


//


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


// Constructors
void WiFi_init();


// Methods
void WiFi_connect(String ssid, String pass="");
void WiFi_wait_connect();
void WiFi_disconnect();
void WiFi_reconnect();

bool WiFi_is_connected();


/* ==================================================
** Extern variables
**
** =============================================== */


//


#endif
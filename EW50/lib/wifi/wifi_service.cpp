/* ==================================================
** Libraries
**
** =============================================== */


#include "wifi_service.h"
#include "wifi_service.deps.h"

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
** Global variables
**
** =============================================== */


//


/* ==================================================
** Global function declaration
**
** =============================================== */


uint8_t get_mode();
uint8_t get_status();
String get_ssid();
String get_pass();
String get_localIP();

void upd_modeBeforeConnect();

void add_evtConnected();
void add_evtGotIP();
void add_evtDisconnect();

bool check_oldWiFi(String ssid, String pass);
bool check_passValid(String pass);


/* ==================================================
** Global function definition
**
** =============================================== */


uint8_t get_mode()
{
    return WiFi.getMode();
}


uint8_t get_status()
{
    return WiFi.status();
}


String get_ssid()
{
    return WiFi.SSID();
}


String get_pass()
{
    return WiFi.psk();
}


String get_localIP()
{
    return WiFi.localIP().toString();
}


void upd_modeBeforeConnect()
{
    WiFiMode_t mode = (WiFiMode_t)get_mode();

    if(mode == WIFI_OFF){
        WiFi.mode(WIFI_STA);
        return;
    }

    if(mode == WIFI_AP){
        WiFi.mode(WIFI_AP_STA);
        return;
    }
}


void add_evtConnected()
{
    static WiFiEventHandler handler = WiFi.onStationModeConnected([](const WiFiEventStationModeConnected &event){
        LOG_I("[WiFi] Connected \"%s\"", get_ssid().c_str());
    });
}


void add_evtGotIP()
{
    static WiFiEventHandler handler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event){
        LOG_I("[WiFi] Got IP: %s", get_localIP().c_str());
    });
}


void add_evtDisconnect()
{
    static WiFiEventHandler handler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected &event){
        LOG_I("[WiFi] Disconnected \"%s\"", get_ssid().c_str());
    });
}


bool check_oldWiFi(String ssid, String pass)
{
    if(ssid.equals(get_ssid()) == false) {return false;}
    if(pass.equals(get_pass()) == false) {return false;}
    return true;
}


bool check_passValid(String pass)
{
    if(pass.isEmpty())      {return true;}
    if(pass.length() < 8)   {return false;}
    return true;
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void WiFi_init()
{
    LOG_I("[WiFi] init");
    add_evtConnected();
    add_evtGotIP();
    add_evtDisconnect();
    WiFi_connect(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASS);
}


void WiFi_connect(String ssid, String pass)
{
    if(check_oldWiFi(ssid, pass))       {return;}
    if(check_passValid(pass) == false)  {return;}

    WiFi_disconnect();
    upd_modeBeforeConnect();
    WiFi.begin(ssid, pass);
    WiFi_wait_connect();
}


void WiFi_wait_connect()
{
    if(get_status() == WL_CONNECTED) {return;}

    LOG_I("[WiFi] Connecting \"%s\"", get_ssid().c_str());

    uint64_t intv = millis();
    while(millis() - intv < WiFi_get_timeWaitConnect()){
        delay(500);
        // LOG_PRINTF(".");
    }
    LOG_PRINTF("\n");
}


void WiFi_disconnect()
{
    WiFi.disconnect();
}


void WiFi_reconnect()
{
    if(get_status() == WL_CONNECTED)
    {
        return;
    }

    else{
        WiFi_wait_connect();
    }
}


bool WiFi_is_connected()
{
    return (get_status() == WL_CONNECTED);
}


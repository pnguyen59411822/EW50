#ifndef wifi_service_deps_h
#define wifi_service_deps_h


#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>

#elif defined(ESP8266)
 #include <ESP8266WiFi.h>
#endif


#endif
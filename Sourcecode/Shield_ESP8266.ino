#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif

#include <MPU9250.h>
MPU9250 IMU(Wire, 0x68);

#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

#include <TinyGPS++.h>                                      // Tiny GPS Plus Library
const double Home_LAT = 0.00000;                          // Your Home Latitude
const double Home_LNG = 0.00000;                          // Your Home Longitude
TinyGPSPlus gps;                                            // Create an Instance of the TinyGPS++ object called gps
#define TIMEZONE 1

#define PC_BAUDRATE     115200
#define GPS_BAUDRATE    115200
#define GPS_RX          D6  //12
#define GPS_TX          D5  //14
#define WIRECLOCK       400000

#include <SoftwareSerial.h>
SoftwareSerial ss(GPS_TX, GPS_RX);

//---
ADC_MODE(ADC_VCC);
#define ESP_Button 0                                        // ESP Flash Button
#define ESP_Led 2                                           // ESP LED

#define Display_X 127
#define Display_Y 63

#define MAXPAGES 10


AsyncWebServer server(80);


#include "A_Variable.h"                                     // Move Variable to it's own File

void setup() {
  InitESP();
  InitSPIFFS();
  InitESPWiFi();
  InitWebhost();
  
  InitOLED();
  InitBME();
  InitGyro();

  GetAll();
}

void loop() {
  Input();
  GetGPS();
  FSM();

  if ( millis() - Bat.last_refresh > Bat.refresh_delay ) {
    GetBattery();
    Bat.last_refresh = millis();
  }

  if ( millis() - BME280.last_refresh > BME280.refresh_delay ) {
    GetBME();
    BME280.last_refresh = millis();
  }

  if ( millis() - MPU.last_refresh > MPU.refresh_delay ) {
    GetGyro();
    MPU.last_refresh = millis();
  }
}

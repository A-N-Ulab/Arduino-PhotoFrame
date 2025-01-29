/*
 |Title: Arduino photoframe code
 |Description: Arduino photoframe made using RaspberryPi Pico and 3.2inch ILI9341 TFT
 |Website: www.glinek.tech
 |Author: Szymon "Glinek" Glinka
 |
 |Change log:
 | - Created this file - 27.01.2025 Szymon Glinka
*/

//=== Importing libraries ===
#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "images.h"
#include <dht11.h>

//=== Defining pins ===
#define TFT_DC 21
#define TFT_CS 17
#define TFT_RST 22
#define SD_MISO 12
#define SD_MOSI 15
#define SD_CS 13
#define SD_SCK 14
#define DHT11PIN 5

//=== Defining colors ===
#define BLACK 0x0000
#define NAVY 0x000F

//=== Creating objects ===
//---- TFT ----
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//---- SD card ----
File root;
//---- WiFi Time ----
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
//---- DHT11 ----
dht11 DHT11;

//=== Defining global variables ===
//---- SD card variables ----
bool sdInitialized = false;
//
//---- Time variables ----
const char *ssid     = "UPC0520860";
const char *password = "Ae8kdjbmaerx";
String timeDate[3] = {"", "", ""};
int dayLightSaving = 0;
//
//---- Screen variables ----
int currentScreen = 0;
bool drawText = false;
//
//---- Delay variables ----
long timeRefreshMainMenu = 0, timeRefreshOtsi = 0;

//==--==--==--== SETUP FUNCTION ==--==--==--==
void setup(void) {
    //=== Serial for debug  purposes ===
    Serial.begin(115200);
    
    //=== Beginning TFT ===
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(2);
    yield();

    //=== SD card setup ===
    //---- Setting SPI pins ---
    SPI1.setRX(SD_MISO);
    SPI1.setTX(SD_MOSI);
    SPI1.setSCK(SD_SCK);
    //
    //---- Initializing SD card ----
    sdInitialized = SD.begin(SD_CS, SPI1);
    //
    //---- Debug ----
    if (!sdInitialized) Serial.println("initialization failed");
    else Serial.println("Wiring is correct and a card is present");
    if(SD.exists("/1.bmp")) Serial.println("file on SD!");

    //=== Connecting to WiFi ===
    //---- Initializing WiFi ----
    WiFi.begin(ssid, password);
    //
    //---- Debug ----
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    timeClient.begin();
}

//==--==--==--== LOOP FUNCTION ==--==--==--==
void loop() {
    if(currentScreen == 0) homeScreen();
    else if(currentScreen == 1) photoFrameScreen();
}



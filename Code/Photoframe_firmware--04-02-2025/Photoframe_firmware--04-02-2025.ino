/*
 |Title: Arduino photoframe code
 |Description: Arduino photoframe made using RaspberryPi Pico and 3.2inch ILI9341 TFT
 |Website: www.glinek.tech
 |Author: Szymon "Glinek" Glinka
 |
 |Change log:
 | - Created this file - 27.01.2025 Szymon Glinka
 | - Fully working code - 04.02.2025 Szymon Glinka
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
#include <EEPROM.h>

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

//=== Preferences addresses ===
#define eeADRfirstBoot 0
#define eeADRcurrentPhoto 1
#define eeADRdlst 2
#define eeADRlastDay 3

//=== Creating objects ===
//---- TFT ----
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//---- SD card ----
File file;
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
bool displayedBit = false;
//
//---- Delay variables ----
long timeRefreshMainMenu = 0, timeRefreshOtsi = 0, timeBackToMenu = 0;
//
//---- EEPROM----
int dstOffset = 1; //*3600
int lastDay = 1, currentPhoto = 1;
int totalPhotos = 100;
int firstBoot = 0;
//
//---- Button ----
int lastState, currentState;
long pressedTime, releasedTime, pressDuration, lastBTNpress;

//==--==--==--== SETUP FUNCTION ==--==--==--==
void setup(void) {
    //=== Serial for debug purposes ===
    Serial.begin(115200);

    //=== Pin init ===
    pinMode(9, INPUT_PULLUP);
    
    //=== Beginning TFT ===
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(2);
    yield();

    //=== Eeprom ===
    //---- Initialize eeprom ----
    EEPROM.begin(5);
    //
    //---- Set variables if first ever boot ----
    if(EEPROM.read(eeADRfirstBoot) != 0){
        EEPROM.write(eeADRfirstBoot, 0);
        EEPROM.write(eeADRcurrentPhoto, 1);
        EEPROM.write(eeADRdlst, 1);
        EEPROM.write(eeADRlastDay, 1);
        EEPROM.commit();
    }
    //---- Read variables if after first boot
    else{
        dstOffset = EEPROM.read(eeADRdlst);
        currentPhoto = EEPROM.read(eeADRcurrentPhoto);
        lastDay = EEPROM.read(eeADRlastDay);
    }
        
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
    if(SD.exists("/Photos/1.bmp")) Serial.println("file on SD!");

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
    //=== Calculating dayLight saving time ===
    dayLightSaving = 3600*dstOffset + 3600;
    
    //=== Screens ===
    if(currentScreen == 0) homeScreen();
    if(currentScreen == 1) photoFrameScreen();
}

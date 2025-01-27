#include <Adafruit_GFX.h>
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <SD.h>

#define TFT_DC 21
#define TFT_CS 17
#define TFT_RST 22
#define SD_MISO 12
#define SD_MOSI 15
#define SD_CS 13
#define SD_SCK 14

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
File root;

bool sdInitialized = false;

void setup(void) {
    Serial.begin(115200);
    
    tft.begin();
    yield();

    SPI1.setRX(SD_MISO);
    SPI1.setTX(SD_MOSI);
    SPI1.setSCK(SD_SCK);
    sdInitialized = SD.begin(SD_CS, SPI1);
    if (!sdInitialized) Serial.println("initialization failed");
    else Serial.println("Wiring is correct and a card is present");
    if(SD.exists("/1.bmp")) Serial.println("file on SD!");

}

void loop() {
    tft.setRotation(2);
    bmpDraw("/1.bmp", 0, 0);
}
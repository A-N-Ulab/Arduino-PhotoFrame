#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9341.h" // Hardware-specific library
#include <SPI.h>
#include <SD.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.

#define TFT_DC 21
#define TFT_CS 17
#define TFT_RST 22
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define SD_MISO 12
#define SD_MOSI 15
#define SD_CS 13
#define SD_SCK 14

File root;
void setup(void) {
    Serial.begin(115200);

    tft.begin();
    
    yield();

    bool sdInitialized = false;
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

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.


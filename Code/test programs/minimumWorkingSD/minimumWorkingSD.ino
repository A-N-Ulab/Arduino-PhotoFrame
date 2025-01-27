
#define SD_MISO 12
#define SD_MOSI 15
#define SD_CS 13
#define SD_SCK 14

// include the SD library:
#include <SPI.h>
#include <SD.h>

File root;

void setup() {
    Serial.begin(115200);

    while (!Serial) {
        delay(1);  // wait for serial port to connect. Needed for native USB port only
    }

    bool sdInitialized = false;
    SPI1.setRX(SD_MISO);
    SPI1.setTX(SD_MOSI);
    SPI1.setSCK(SD_SCK);
    sdInitialized = SD.begin(SD_CS, SPI1);

    if (!sdInitialized) Serial.println("initialization failed");
    else Serial.println("Wiring is correct and a card is present");

    if(SD.exists("1.bmp")) Serial.println("file on SD!");
}

void loop(void) {
  // nothing happens after setup finishes.
}

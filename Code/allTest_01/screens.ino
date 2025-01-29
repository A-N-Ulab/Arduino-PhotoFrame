void homeScreen(){
    //=== Variables ===
    String temp, humid;
    dayLightSaving = 3600;
    
    if((millis() >= timeRefreshMainMenu + 1000)){
        //---- Setting basic text value - color ----
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

        //=== Displaying time and date ===
        //---- Set text size to 3 ----
        tft.setTextSize(3);
        //
        //---- Get time and date from server ----
        convertTime2String(dayLightSaving);
        //
        //---- Print time and date on TFT ----
        tft.setCursor(50, 148);
        tft.println(timeDate[0]);
        tft.setCursor(40, 175);
        tft.println(timeDate[2]);
        tft.setCursor(31, 208);
        tft.println(timeDate[1]);

        //=== Read DHT temp and humid ===
        int dhtReading = DHT11.read(DHT11PIN);
        //
        //---- Convert data to strings ----
        temp = String((float)DHT11.temperature, 0) + "'C";
        humid = String((float)DHT11.humidity, 0) + "%";
        //
        //---- Print temp and humid to tft ----
        tft.setCursor(25, 271);
        tft.print(temp);
        tft.setCursor(160, 271);
        tft.print(humid);

        //=== Refresh every second ===
        timeRefreshMainMenu = millis();
    }

    if(millis() >= timeRefreshOtsi + 125){
        tft.drawBitmap(0, 15, (const unsigned char *)otsi_normal, 240, 120, ILI9341_WHITE);
    }
    if(millis () >= timeRefreshOtsi + 3150){
        tft.fillRect(123, 45, 10, 14, ILI9341_BLACK);
        tft.fillRect(166, 48, 8, 12, ILI9341_BLACK);
        tft.drawBitmap(0, 15, (const unsigned char *)otsi_blinking, 240, 120, ILI9341_WHITE);
        timeRefreshOtsi = millis();
    }
}

void photoFrameScreen(){
    //bmpDraw("/1.bmp", 0, 0);
    int a;
}

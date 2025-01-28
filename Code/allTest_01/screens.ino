void homeScreen(){
    dayLightSaving = 3600;
    if(millis() >= timeRefreshMainMenu + 1000){
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
        tft.setCursor(31, 202);
        tft.println(timeDate[1]);

        //=== Refresh every second ===
        timeRefreshMainMenu = millis();
    }

    if(millis() >= timeRefreshOtsi + 125){
        tft.drawBitmap(50, 56, (const unsigned char *)otsi_normal, 128, 64, ILI9341_Yellow);
    }
}

void photoFrameScreen(){
    //bmpDraw("/1.bmp", 0, 0);
    int a;
}

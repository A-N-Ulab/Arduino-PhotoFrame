void homeScreen(){
    //=== Variables ===
    String temp, humid;
    
    //=== Home screen - time, date, temp, etc. ===
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

    //=== Otsi image blinking ===
    //---- Normal bitmap ----
    if(millis() >= timeRefreshOtsi + 125){
        tft.drawBitmap(0, 15, (const unsigned char *)otsi_normal, 240, 120, ILI9341_WHITE);
    }
    //---- Blinking bitmap for 125ms ----
    if(millis () >= timeRefreshOtsi + 3150){
        tft.fillRect(123, 45, 10, 14, ILI9341_BLACK);
        tft.fillRect(166, 48, 8, 12, ILI9341_BLACK);
        tft.drawBitmap(0, 15, (const unsigned char *)otsi_blinking, 240, 120, ILI9341_WHITE);
        timeRefreshOtsi = millis();
    }

    //=== Read button - long and short press ===
    //---- Read btn state ----
    currentState = digitalRead(9);
    //
    //---- Count pressed and released time ----
    if(lastState == HIGH && currentState == LOW)
        pressedTime = millis();
    else if(lastState == LOW && currentState == HIGH){
        releasedTime = millis();
        //---- Calculate total duration of press ----
        long pressDuration = releasedTime - pressedTime;
        //
        //---- If press was a short press change screen to 1 to display image ----
        if(pressDuration < 1000){
            currentScreen = 1;
            timeBackToMenu = millis();
        }
        //---- If press was a long press, change daylight saving time ----
        if(pressDuration > 1000){
            //-- If daylight saving time is active change it to zero and save to EEPROM ----
            if(dstOffset == 1){
                dstOffset = 0;
                EEPROM.write(eeADRdlst, dstOffset);
                EEPROM.commit();
            }
            //-- If daylight saving time is zero change it to active and save to EEPROM ----
            else{
                dstOffset = 1;
                EEPROM.write(eeADRdlst, dstOffset);
                EEPROM.commit();
            }
        }
    } 
    //
    //---- Saving last btn state ----
    lastState = currentState;
}

void photoFrameScreen(){
    //=== Declaration of variables ===
    int currentDay;
    String path = "photos/"; 
    int pathLen;
    

    //=== Get current day of the month ===
    currentDay = getJustDay(dayLightSaving);

    //=== Change current photo if it's the next day and save to EEPROM ===
    if(currentDay != lastDay){
        currentPhoto++;
        lastDay = currentDay;
        EEPROM.write(eeADRcurrentPhoto, currentPhoto);
        EEPROM.write(eeADRlastDay, lastDay);
        EEPROM.commit();
    }

    //=== If reached the end of photos, reset to zero and save to EEPROM ===
    if(currentPhoto > totalPhotos){
        currentPhoto = 1;
        EEPROM.write(eeADRcurrentPhoto, currentPhoto);
        EEPROM.commit();
    }

    //=== Create path to file from specified photo num ===
    //---- Create string path ----
    path = path + String(currentPhoto) + ".bmp";
    //
    //---- Convert path to char ----
    pathLen = path.length() + 1; 
    char pathArray[pathLen];
    path.toCharArray(pathArray, pathLen);

    //=== Draw photo ===
    if(displayedBit == false){
        bmpDraw(pathArray, 0, 0);
        displayedBit = true;
    }
    
    //=== When btn pressed go back to main menu ===
    if(digitalRead(9) == LOW){
        tft.fillScreen(ILI9341_BLACK);
        displayedBit = false;
        currentScreen = 0;
    }
}

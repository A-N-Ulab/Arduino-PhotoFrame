void convertTime2String(int timeOffs){
    //=== Declarations of variables ===
    String weekDays[7]={" Sunday  ", " Monday  ", " Tuesday ", "Wednesday", "Thursday ", " Friday  ", "Saturday "};
    String timeString, dateString, wholeString, hString, mString, sString, mmdString, mmString;

    //=== Get time ===
    timeClient.setTimeOffset(timeOffs);
    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime); 

    //=== Calculating time and date ===
    int h = timeClient.getHours();
    int m = timeClient.getMinutes();
    int s = timeClient.getSeconds();
    int d = timeClient.getDay();
    int mmd = ptm->tm_mday;
    int mm = ptm->tm_mon+1;
    int y = ptm->tm_year+1900;
    
    //=== Adding "0" before numbers so it looks better ===
    if(h <= 9) hString = "0" + String(h);
    else hString = String(h);
    if(m <= 9) mString = "0" + String(m);
    else mString = String(m);
    if(s <= 9) sString = "0" + String(s);
    else sString = String(s);
    if(mmd <= 9) mmdString = "0" + String(mmd);
    else mmdString = String(mmd);
    if(mm <= 9) mmString = "0" + String(mm);
    else mmString = String(mm);


    //=== Creating final string ===
    timeString = hString + ":" + mString + ":" + sString;
    dateString = mmdString + "." + mmString + "." + String(y);
    //wholeString = timeString + " on " + weekDays[d] + ", " + dateString;

    //=== Returning time and date ===
    timeDate[0] = timeString;
    timeDate[1] = dateString;
    timeDate[2] = weekDays[d];
}

int getJustDay(int timeOffs){
    //=== Get time ===
    timeClient.setTimeOffset(timeOffs);
    timeClient.update();

    //=== Calculate and return current day of month ===
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int mmd = ptm->tm_mday;
    return mmd;
}
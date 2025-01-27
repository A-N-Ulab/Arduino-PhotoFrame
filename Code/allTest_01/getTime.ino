String convertTime2String(int timeOffs){
    //=== Declarations of variables ===
    String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    String timeString, dateString, wholeString, hString, mString, sString;

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

    //=== Creating final string ===
    timeString = hString + ":" + mString + ":" + sString;
    dateString = String(mmd) + "." + String(mm) + "." + String(y);
    wholeString = timeString + " on " + weekDays[d] + ", " + dateString;

    //=== Returning time and date ===
    return wholeString;
}
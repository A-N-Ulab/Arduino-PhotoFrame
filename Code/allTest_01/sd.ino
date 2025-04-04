void readFromSD(){
    file = SD.open("config.txt");
    rawFromSD = file.readString();
    file.close();

    String placeHolderCurrent = "", placeHolderTotal = "";

    placeHolderCurrent = getValue(rawFromSD, '|', 0);
    placeHolderTotal = getValue(rawFromSD, '|', 1);

    currentAndTotalPhotos[0] = getValue(placeHolderCurrent, ':', 1);
    currentAndTotalPhotos[1] = getValue(placeHolderTotal, ':', 1);
}

void writeToSD(String dataToWrite){
    SD.remove("config.txt");
    file = SD.open("config.txt", FILE_WRITE);
    file.println(dataToWrite);
    file.close();
}

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
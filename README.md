# PhotoFrame
## Code
The lates working code is `Photoframe_firmware--04-02-2025` located in `code` folder
**IMPORTANT!** for this code to compile you will have to copy library from `Code/library for dht11` to your Arduino library folder

## Repo structure
```
- Cad files
  |- Assembly
  |- freecad
  |- step
  |- STL
- Code
  |- allTest_01
  |- library for dht11
  |- Photoframe_firmware--04-02-2025
  |- test programs
- Graphics
  |- Otsi
- Photos to SD
```
- `Cad files` - folder containing step models, STL meshes and freecad project. Also contains folder with freecad assembly - [A2plus](https://github.com/kbwbe/A2plus)
- `Code` - folder containing test programs for the whole photoframe program used to test individual components as well as completed code. Contains library for dht11 sensor
- `Graphics` - folder containing all graphics, including 240x120px Otsi
- `Photos to SD` - folder containing bitmaps of all photos that are gonna be displayed

## Photo setup
- 24bit bitmap
- 320px height
- 240px width

## Credits
- code for displaying bitmaps is based on [work of](https://forums.adafruit.com/viewtopic.php?t=141979) `Rarday` on adafruit forum but with slight modifications so it works
- getting time from webserver is based on [work of](https://github.com/tehniq3/NTPclock_RPi_Pico_W/blob/main/ntp_test_serial.ino) `tehniq3` on github

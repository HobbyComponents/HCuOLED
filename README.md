# HCuOLED
An Arduino library for SSD1307 and SH1106 based OLED displays

![Alt text](http://blog.hobbycomponents.com/wp-content/uploads/2015/04/1557.jpg "BLink")


This Arduino library will allow you to display various text, graphics and and bitmaps on SSD1307 and SH1106 based uOLED displays. The library has been written specifically for our own uOLED displays including the following:

Hobby Components 0.96" uOLED displays (HCMODU0050 & HCMODU0052):
http://hobbycomponents.com/displays/400-ssd1306-128x64-pixel-oled-display-module-white
http://hobbycomponents.com/displays/399-ssd1306-128x64-pixel-oled-display-module-blue

Hobby Components 1.3" uOLED displays (HCMODU0058 & HCMODU0059):
http://hobbycomponents.com/displays/621-3-sh1106-uoled-display-module-white
http://hobbycomponents.com/displays/622-3-sh1106-uoled-display-module-white

WeMos D1 mini OLED shield (HCWEMO0007):
[LINK TBA]

The library makes use of the Arduino's SPI (I2C support now added) interface to drive the displays in their default SPI configuration. However, the library is capable of driving multiple displays with a mix of previously mentioned controller types all from one Arduino. Each additional display will only require 3 additional digital pins.


You will need to download and unzip this library to the Arduino development environments library area.

On Windows: 
My Documents\Arduino\libraries\

On Mac: 
Documents/Arduino/libraries/
or similarly for Linux.



More information on how to use this library can be found in the software section of our support forum:
http://forum.hobbycomponents.com/viewtopic.php?f=58&t=1817


Version 0.2 (06/12/16) updates:

Added compatability with ESP8266
Added support for uOLED displays in I2C mode
Added support for WeMos D1 mini OLED shield (see item HCWEMO0007)
Made speed improvement to erase function (thanks to vladyslav-savchenko)


Version 0.3 (22/05/17)

Updated to include 0.9" 128x32 screens (HCMODU0118 & HCMODU0119). Use option SSD1306_128_32 for DisplayType or see example sketch HCuOLED_Things_Example_For_HCMODU0118_HCMODU0119.ino

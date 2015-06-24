# HCuOLED
An Arduino library for SSD1307 and SH1106 based OLED displays

![Alt text](http://blog.hobbycomponents.com/wp-content/uploads/2015/04/1557.jpg "BLink")


This Arduino library will allow you to display various text, graphics and and bitmaps on SSD1307 and SH1106 uOLED displays. The library has been written specifically for our own uOLED displays including the following:

Hobby Components 0.96" uOLED displays (HCMODU0050 & HCMODU0052):
http://hobbycomponents.com/displays/400-ssd1306-128x64-pixel-oled-display-module-white
http://hobbycomponents.com/displays/399-ssd1306-128x64-pixel-oled-display-module-blue

Hobby Components 1.3" uOLED displays (HCMODU0058 & HCMODU0059):
http://hobbycomponents.com/displays/621-3-sh1106-uoled-display-module-white
http://hobbycomponents.com/displays/622-3-sh1106-uoled-display-module-white


The library makes use of the Arduino's SPI interface to drive the displays in their default SPI configuration. However, the library is capable of driving multiple displays with a mix of previously mentioned controller types all from one Arduino. Each additional display will only require 3 additional digital pins.



You will need to download and unzip this library to the Arduino development environments library area.

On Windows: 
My Documents\Arduino\libraries\

On Mac: 
Documents/Arduino/libraries/
or similarly for Linux.



More information on how to use this library can be found in the software section of our support forum:
http://forum.hobbycomponents.com/viewtopic.php?f=58&t=1817

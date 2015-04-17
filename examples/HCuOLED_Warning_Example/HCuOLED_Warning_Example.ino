/* FILE:    HCuOLED_Warning_Example
   DATE:    16/04/15
   VERSION: 0.1
   
REVISIONS:

12/03/15 Created version 0.1

This is an example of how to use the DrawMode function to display a flashing
warning sign.

To use this example connect your uOLED display to the following pins of your 
Arduino:


MODULE..........ARDUINO
GND.............GND
VCC.............3.3V
D0 (CLK)........D13
D1 (DATA).......D11
RST (RESET).....D8
DC..............D9
CS (SS).........D10


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of promoting products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, 
WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR
LACK OF NEGLIGENCE. HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE
FOR ANY DAMAGES INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR 
CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER. */

#include "HCuOLED.h"
#include "SPI.h"


/* Digital pin number for the displays chip select pin */
#define CS_DI 10
/* Digital pin number for the displays data/command pin */
#define DC_DI 9
/* Digital pin number for the displays reset pin */
#define RST_DI 8


/* Create an instance of the library (uncomment one of the lines below) */
//HCuOLED HCuOLED(SSD1307, SS_DI, DC_DI, RST_DI); // For SSD1307 displays (HCMODU0050 & HCMODU0052)
HCuOLED HCuOLED(SH1106, CS_DI, DC_DI, RST_DI); // For SH1106 displays (HCMODU0058 & HCMODU0059)


void setup() 
{
  /* Reset the display */
  HCuOLED.Reset();
}

void loop() 
{
  /* DrawMode defaults to NORMAL but we include this line for demonstation purposes */
  HCuOLED.DrawMode(NORMAL);
  
  /* Display a number using a large 4 line LCD style font */
  HCuOLED.Cursor(20,16);
  HCuOLED.SetFont(LCDLarge_24pt);
  HCuOLED.Print("WARNING!!");

  /* Set draw mode to INVERT mode. This will reverse the state of any pixes written to on 
     the display */
  HCuOLED.DrawMode(INVERT);

  while(1)
  {
    /* Draw a solid box around the screen. As DrawMode is set to inver it will also reverse 
    the text */
    HCuOLED.Rect(0,0,127,63, SOLID);
  
    /* Output the display buffer to the screen */
    HCuOLED.Refresh();
  
    delay(100);
  }
}

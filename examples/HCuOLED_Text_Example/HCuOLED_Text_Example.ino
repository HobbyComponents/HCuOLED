/* FILE:    HCuOLED_Text_Example
   DATE:    16/04/15
   VERSION: 0.1
   
REVISIONS:

12/03/15 Created version 0.1


This is an example of how to display text and numbers using the HCuOLED library 
on a SSD1307 or SH1106 based OLED display module such as:

Hobby Components 0.96" uOLED displays (HCMODU0050 & HCMODU0052)
Hobby Components 1.3" uOLED displays (HCMODU0058 & HCMODU0059)

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
  /* Display some text using a small 8x8 fixed width font */
  HCuOLED.Cursor(16,0);
  HCuOLED.SetFont(Terminal_8pt);
  HCuOLED.Print("HELLO WORLD");

  /* Display some text using a medium 2 line proportional font */  
  HCuOLED.Cursor(4,20);
  HCuOLED.SetFont(MedProp_11pt);
  HCuOLED.Print("HELLO WORLD");
  
  /* Display a number using a large 4 line LCD style font */
  HCuOLED.Cursor(28,40);
  HCuOLED.SetFont(LCDLarge_24pt);
  HCuOLED.Print(-12345, 2);
  
  /* Output the display buffer to the screen */
  HCuOLED.Refresh();
  
  /* Nothing more to do */
  while(1);
}

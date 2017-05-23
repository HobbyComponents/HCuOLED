/* FILE:    HCuOLED_Things_Example_For_HCMODU0118_HCMODU0119   
   DATE:    23/05/17
   VERSION: 0.1
   
REVISIONS:

123/05/17 Created version 0.1

This example is specifically written for the 128 x 64 pixel 0.9" OLED screens
(HCMODU0118 & HCMODU0119). The example uses the line and rectangle graphic 
functions together with the INVERT DrawMode to create a simple animation.

Please visit http://forum.hobbycomponents.com/viewtopic.php?f=58&t=1817
for more information on how to use all the features within this library.

To use this example connect your uOLED display to the following pins of your 
Arduino:


MODULE..........ARDUINO UNO
GND.............GND
VCC.............3.3V
SCL.............A5
SDA.............A4


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


/* Array indexes for the X and Y coordinates */
#define X1 0
#define Y1 1
#define X2 2
#define Y2 3

/* Arrays to store coordinates and direction for the line, rectangle and bitmap */
byte Box[4] = {1,1,20,20};
byte BoxDir[4] = {1,1,1,1};
byte Line[4] = {100,25,120,15};
byte LineDir[4] = {-1,-1,-1,-1};
byte Bitmap[2] = {5,5};
byte BitmapDir[2] = {-1,-1};

/* I2C address of the display */
#define I2C_ADD 0x3C

/* Create an instance of the library */
HCuOLED HCuOLED(SSD1306_128_32, I2C_ADD);



void setup() 
{
  /* Reset the display */
  HCuOLED.Reset();
}

void loop() 
{
  /* Display some text using a large 4 line LCD style font */
  HCuOLED.Cursor(20,0);
  HCuOLED.SetFont(LCDLarge_24pt);
  HCuOLED.Print("HCuOLED");

  /* Display some text using a small 8x8 fixed width font */
  HCuOLED.SetFont(Terminal_8pt);
  HCuOLED.Cursor(36,25);
  HCuOLED.Print("LIBRARY");

  HCuOLED.Rect(21,25,32,31, SOLID);
  HCuOLED.Rect(96,25,107,31, SOLID);
 

  /* Change the draw mode from NORMAL to INVERT */
  HCuOLED.DrawMode(INVERT);
  while(1)
  {
    /* Move the positions of the 3 objects */
    MoveRect();
    MoveLine();
    
    /* Draw the objects to the display buffer */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID);
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
    
    /* Write the display buffer to the screen */
    HCuOLED.Refresh();
    
    /* Draw the objects again. As we are in INVERT mode this will remove them */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID); 
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
  }
}


/* Update the X and Y coordinates for the box */
void MoveRect(void)
{
  if(Box[X1] == 0 || Box[X1] == 127)
    BoxDir[X1] *= -1;
  Box[X1] += BoxDir[X1];
  
  if(Box[Y1] == 0 || Box[Y1] == 31)
    BoxDir[Y1] *= -1;
  Box[Y1] += BoxDir[Y1];
  
  if(Box[X2] == 0 || Box[X2] == 127)
    BoxDir[X2] *= -1;
  Box[X2] += BoxDir[X2];
  
  if(Box[Y2] == 0 || Box[Y2] == 31)
    BoxDir[Y2] *= -1;
  Box[Y2] += BoxDir[Y2];   
}

/* Update the X and Y coordinates for the Line */
void MoveLine(void)
{
  if(Line[X1] == 0 || Line[X1] == 127)
    LineDir[X1] *= -1;
  Line[X1] += LineDir[X1];
  
  if(Line[Y1] == 0 || Line[Y1] == 31)
    LineDir[Y1] *= -1;
  Line[Y1] += LineDir[Y1];
  
  if(Line[X2] == 0 || Line[X2] == 127)
    LineDir[X2] *= -1;
  Line[X2] += LineDir[X2];
  
  if(Line[Y2] == 0 || Line[Y2] == 31)
    LineDir[Y2] *= -1;
  Line[Y2] += LineDir[Y2];   
}

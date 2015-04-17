/* FILE:    HCuOLED_Things_Example
   DATE:    16/04/15
   VERSION: 0.1
   
REVISIONS:

12/03/15 Created version 0.1


This example uses the line, rectangle and bitmap graphic functions together with 
the INVERT DrawMode to create a simple animation.

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

/* Example bitmap */
const PROGMEM byte Tiny_Logo_Resistor[] =
{
  0xC0, 0xE0, 0x30, 0x30, 0xF0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x38, 0x0E, 0x07, 0x1E, 0x78, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x70, 0x1C, 0x07, 0x0F, 0x3C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x3C, 0x0F, 0x07, 0x1C, 0x70, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x78, 0x1E, 0x07, 0x0E, 0x38, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xF0, 0x30, 0x30, 0xE0, 0xC0, 
  0x00, 0x01, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x3C, 0x38, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1E, 0x38, 0x1C, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x38, 0x38, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1C, 0x38, 0x1E, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x38, 0x3C, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x01, 0x00, 
};


/* Digital pin number for the displays chip select pin */
#define CS_DI 10
/* Digital pin number for the displays data/command pin */
#define DC_DI 9
/* Digital pin number for the displays reset pin */
#define RST_DI 8

/* Array indexes for the X and Y coordinates */
#define X1 0
#define Y1 1
#define X2 2
#define Y2 3

/* Arrays to store coordinates and direction for the line, rectangle and bitmap */
byte Box[4] = {1,1,20,20};
byte BoxDir[4] = {1,1,1,1};
byte Line[4] = {100,25,120,55};
byte LineDir[4] = {-1,-1,-1,-1};
byte Bitmap[2] = {40,40};
byte BitmapDir[2] = {-1,-1};



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
  HCuOLED.SetFont(Terminal_8pt);
  HCuOLED.Cursor(44,0);
  HCuOLED.Print("HOBBY");
  HCuOLED.Cursor(20,10);
  HCuOLED.Print("COMPONENTS");

  /* Display a number using a large 4 line LCD style font */
  HCuOLED.Cursor(20,24);
  HCuOLED.SetFont(LCDLarge_24pt);
  HCuOLED.Print("HCuOLED");
 
  /* Change the draw mode from NORMAL to INVERT */
  HCuOLED.DrawMode(INVERT);
  while(1)
  {
    /* Move the positions of the 3 objects */
    MoveRect();
    MoveLine();
    MoveBitmap();
    
    /* Draw the objects to the display buffer */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID);
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
    
    HCuOLED.Cursor(Bitmap[X1],Bitmap[Y1]);
    HCuOLED.Bitmap(84, 2, Tiny_Logo_Resistor);
    
    /* Write the display buffer to the screen */
    HCuOLED.Refresh();
    
    /* Draw the objects again. As we are in INVERT mode this will remove them */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID); 
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
    
    HCuOLED.Cursor(Bitmap[X1],Bitmap[Y1]);
    HCuOLED.Bitmap(84, 2, Tiny_Logo_Resistor); 
  }
}


/* Update the X and Y coordinates for the box */
void MoveRect(void)
{
  if(Box[X1] == 0 || Box[X1] == 127)
    BoxDir[X1] *= -1;
  Box[X1] += BoxDir[X1];
  
  if(Box[Y1] == 0 || Box[Y1] == 63)
    BoxDir[Y1] *= -1;
  Box[Y1] += BoxDir[Y1];
  
  if(Box[X2] == 0 || Box[X2] == 127)
    BoxDir[X2] *= -1;
  Box[X2] += BoxDir[X2];
  
  if(Box[Y2] == 0 || Box[Y2] == 63)
    BoxDir[Y2] *= -1;
  Box[Y2] += BoxDir[Y2];   
}

/* Update the X and Y coordinates for the Line */
void MoveLine(void)
{
  if(Line[X1] == 0 || Line[X1] == 127)
    LineDir[X1] *= -1;
  Line[X1] += LineDir[X1];
  
  if(Line[Y1] == 0 || Line[Y1] == 63)
    LineDir[Y1] *= -1;
  Line[Y1] += LineDir[Y1];
  
  if(Line[X2] == 0 || Line[X2] == 127)
    LineDir[X2] *= -1;
  Line[X2] += LineDir[X2];
  
  if(Line[Y2] == 0 || Line[Y2] == 63)
    LineDir[Y2] *= -1;
  Line[Y2] += LineDir[Y2];   
}

/* Update the X and Y coordinates for the bitmap */
void MoveBitmap(void)
{
  if(Bitmap[X1] == 0 || Bitmap[X1] == 43)
    BitmapDir[X1] *= -1;
  Bitmap[X1] += BitmapDir[X1];
  
  if(Bitmap[Y1] == 0 || Bitmap[Y1] == 47)
    BitmapDir[Y1] *= -1;
  Bitmap[Y1] += BitmapDir[Y1];
}

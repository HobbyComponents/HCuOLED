/* FILE:    HCuOLED_Things_Example_WeMos_OLED_Version
   DATE:    05/12/16
   VERSION: 0.1
   
REVISIONS:

12/03/15 Created version 0.1

This example shows how to uses the HCOLED library with the WeMos D1 mini uOLED
shield. The sketch uses the line, rectangle and bitmap graphic functions together with 
the INVERT DrawMode to create a simple animation.

The sketch assumes what the shield with be connected to a WeMos D1 mini or mini Pro

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

/* Include the standard wire library */
#include <Wire.h>

/* Example bitmap (48x8 pixels) */
const PROGMEM byte  Tiny_Logo_Resistor[]={0x38, 0x44, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x40, 0xE0, 0x18, 0x04, 0x03, 0x0C, 0x30, 
                                          0x60, 0xC0, 0x30, 0x0C, 0x03, 0x0C, 0x10, 0x60, 0xC0, 0x30, 0x0C, 0x03, 0x0C, 0x10, 0x60, 0xC0, 
                                          0x30, 0x0C, 0x03, 0x04, 0x18, 0x60, 0xC0, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x44, 0x38};


/* I2C address of the display */
#define I2C_ADD 0x3C

/* Array indexes for the X and Y coordinates */
#define X1 0
#define Y1 1
#define X2 2
#define Y2 3

/* Arrays to store coordinates and direction for the line, rectangle and bitmap */
byte Box[4] = {1,1,20,20};
byte BoxDir[4] = {1,1,1,1};
byte Line[4] = {10,25,20,5};
byte LineDir[4] = {-1,-1,-1,-1};
byte Bitmap[2] = {10,10};
byte BitmapDir[2] = {-1,-1};

/* Create an instance of the library for the WeMos D1 OLED shield */
HCuOLED HCuOLED(WEMOS_D1_MINI_OLED, I2C_ADD);

void setup() 
{
  /* Initialise the I2C wire library. For WeMos D1 I2C port is on pins D4 & D5 */
  Wire.begin(4, 5);

  /* Reset the display */
  HCuOLED.Reset();

    /* Display some text using a small 8x8 fixed width font */
  HCuOLED.SetFont(Terminal_8pt);
  HCuOLED.Cursor(12,0);
  HCuOLED.Print("HOBBY");
  HCuOLED.Cursor(0,10);
  HCuOLED.Print("COMPONENTS");

  /* Display a number using a large 4 line LCD style font */
  HCuOLED.Cursor(0,24);
  HCuOLED.SetFont(LCDLarge_24pt);
  HCuOLED.Print("uOLED");
 
  /* Change the draw mode from NORMAL to INVERT */
  HCuOLED.DrawMode(INVERT); 
}

void loop() 
{
    /* Move the positions of the 3 objects */
    MoveRect();
    MoveLine();
    MoveBitmap();
    
    /* Draw the objects to the display buffer */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID);
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
    
    HCuOLED.Cursor(Bitmap[X1],Bitmap[Y1]);
    //HCuOLED.Bitmap(84, 2, Tiny_Logo_Resistor);
    HCuOLED.Bitmap(48, 1, Tiny_Logo_Resistor);
    
    /* Write the display buffer to the screen */
    HCuOLED.Refresh();
    
    /* Draw the objects again. As we are in INVERT mode this will remove them */
    HCuOLED.Rect(Box[X1],Box[Y1],Box[X2],Box[Y2], SOLID); 
    HCuOLED.Line(Line[X1],Line[Y1],Line[X2],Line[Y2]);
    
    HCuOLED.Cursor(Bitmap[X1],Bitmap[Y1]);
    HCuOLED.Bitmap(48, 1, Tiny_Logo_Resistor);
}


/* Update the X and Y coordinates for the box */
void MoveRect(void)
{
  if(Box[X1] == 0 || Box[X1] == 63)
    BoxDir[X1] *= -1;
  Box[X1] += BoxDir[X1];
  
  if(Box[Y1] == 0 || Box[Y1] == 47)
    BoxDir[Y1] *= -1;
  Box[Y1] += BoxDir[Y1];
  
  if(Box[X2] == 0 || Box[X2] == 63)
    BoxDir[X2] *= -1;
  Box[X2] += BoxDir[X2];
  
  if(Box[Y2] == 0 || Box[Y2] == 47)
    BoxDir[Y2] *= -1;
  Box[Y2] += BoxDir[Y2];   
}

/* Update the X and Y coordinates for the Line */
void MoveLine(void)
{
  if(Line[X1] == 0 || Line[X1] == 63)
    LineDir[X1] *= -1;
  Line[X1] += LineDir[X1];
  
  if(Line[Y1] == 0 || Line[Y1] == 47)
    LineDir[Y1] *= -1;
  Line[Y1] += LineDir[Y1];
  
  if(Line[X2] == 0 || Line[X2] == 63)
    LineDir[X2] *= -1;
  Line[X2] += LineDir[X2];
  
  if(Line[Y2] == 0 || Line[Y2] == 47)
    LineDir[Y2] *= -1;
  Line[Y2] += LineDir[Y2];   
}

/* Update the X and Y coordinates for the bitmap */
void MoveBitmap(void)
{
  if(Bitmap[X1] == 0 || Bitmap[X1] == 15)
    BitmapDir[X1] *= -1;
  Bitmap[X1] += BitmapDir[X1];
  
  if(Bitmap[Y1] == 0 || Bitmap[Y1] == 39)
    BitmapDir[Y1] *= -1;
  Bitmap[Y1] += BitmapDir[Y1];
}

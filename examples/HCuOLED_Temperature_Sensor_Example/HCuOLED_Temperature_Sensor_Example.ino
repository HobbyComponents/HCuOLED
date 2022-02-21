/* FILE:    HCuOLED_Temperature_Sensor_Example
   DATE:    16/04/15
   VERSION: 0.1
   
REVISIONS:

12/03/15 Created version 0.1


This is an example of how to display the output from a temperature sensor (LM35)
connected the one of the analogue inputs using the HCuOLED library. If this sketch
you will need an LM35 temperature sensor (HCSENS0011) connected to analogue pin A0.

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

/* Define the analogue pin used to read the temperature sensor (A0) */
#define LM35Pin 0


/* Create an instance of the library (uncomment one of the lines below) */
//HCuOLED HCuOLED(SSD1307, CS_DI, DC_DI, RST_DI); // For SSD1307 displays (HCMODU0050 & HCMODU0052)
//HCuOLED HCuOLED(SH1106, CS_DI, DC_DI, RST_DI); // For SH1106 displays (HCMODU0058 & HCMODU0059)

/* Stores the current temperature reading */
float Temperature;

void setup() 
{
  /* Reset the display */
  HCuOLED.Reset();
  
  /* Set the analogue reference used by the ADC inputs 
     to the internal 1.1V reference */ 
  analogReference(INTERNAL);
}



void loop() 
{
  
  /* Display some text using a medium 2 line proportional font */  
  HCuOLED.SetFont(MedProp_11pt);
  HCuOLED.Cursor(4,10);
  HCuOLED.Print("TEMPERATURE");

  /* Set the font to a large 4 line LCD style font */
  HCuOLED.SetFont(LCDLarge_24pt);
  while(1)
  {
    /* Clear the area where the temperature will be displayed */
    HCuOLED.Erase(40,40,88,63);
    /* Set the text cursor to that location */
    HCuOLED.Cursor(40,40);
    
    /* Read the current temperature from the LM35 sensor */
    Temperature = analogRead(LM35Pin) / 9.31;

    /* Write the temperature to the display buffer */
    HCuOLED.Print(Temperature, 4, 1);  
       
    /* Output the display buffer to the screen */
    HCuOLED.Refresh();
  }
}

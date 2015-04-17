/* FILE:    HCuOLED.h
   DATE:    16/04/15
   VERSION: 0.1
   AUTHOR:  Andrew Davies

16/04/15 version 0.1: Original version

Library header for SSD1307 and SH1106 based OLED displays. In particular this 
library has been written for the following displays:

Hobby Components 0.96" uOLED displays (HCMODU0050 & HCMODU0052)
Hobby Components 1.3" uOLED displays (HCMODU0058 & HCMODU0059)


You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.

THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/


#ifndef HCuOLED_h
#define HCuOLED_h

#include "SPI.h"
#include "Arduino.h"
#include <avr/pgmspace.h>

extern const PROGMEM byte Terminal_8pt[];
extern const PROGMEM byte MedProp_11pt[];
extern const PROGMEM byte LCDLarge_24pt[];

/* Supported display controller types */
#define SSD1307 0
#define SH1106 1

/* Display resolution */
#define BUFFERCOLSIZE 128
#define BUFFERROWSIZE 8

/* Display command register addresses */
#define COLLOWADD 0x00
#define COLHIGHADD 0x10
#define DISPLAYONADD 0xAE
#define PAGEADD 0xB0
#define STARTLINEADD 0x40
#define SCANDIRECTIONADD 0xC0
#define SEGMENTMAPADD 0xA0

/* Command register parameters */
#define SCANDIRNORMAL 0x00
#define SCANDIRREVERSE 0x08
#define SEGMENTMAPNORMAL 0
#define SEGMENTMAPREVERSE 1


/* Various draw modes */
enum HCuOLEDDrawModes
{
	NORMAL    = 1,
	INVERT    = 2,
	CLEAR     = 3,
	OUTLINE   = 4,
	SOLID     = 5
	
};


class HCuOLED
{
  public:
  HCuOLED(byte DisplayType, byte SS_DIO, byte DC_DIO, byte RST_DIO);
  void Reset(void);
  void Refresh(void);
  static void ClearBuffer(void);
  //void ClearDisplayRam(void);
  void Flip_H(void);
  void Flip_V(void);
  static void Bitmap(byte Cols, byte ByteRows, const byte BitmapData[]);
  static void Cursor(byte X, byte Y);
  static void Print(char TextString[]);
  static void Print(long Value);
  static void Print(int long Value, byte DecimalPlaces);
  static void Print(float value, byte digits, byte DecimalPlaces);
  static void SetFont(const byte *Font);
  static void Plot(byte X, byte Y);
  static void Line(byte X1, byte Y1, byte X2, byte Y2);
  static void Rect(byte X1, byte Y1, byte X2, byte Y2, byte FillMode);
  static void Erase(byte X1, byte Y1, byte X2, byte Y2);
  static void DrawMode(byte DrawMode);

  
  private:
  void _CommandMode(void);
  void _DisplayMode(void);
  static void _WriteChar(char character);
  byte _SS;
  byte _DC;
  byte _RST;
  boolean _V_Ori;
  boolean _H_Ori;
  static byte _XPos;
  static byte _YPos;
  static const byte *_FontType;
  static const unsigned int *_FontDescriptor;
  static byte _FontHight;
  byte _StartCol;
  byte _DisplayRAMColSize; 
  static byte _DrawMode;
}; 

#endif
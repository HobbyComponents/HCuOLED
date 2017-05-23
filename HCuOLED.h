/* FILE:    HCuOLED.h
   DATE:    22/05/17
   VERSION: 0.3
   AUTHOR:  Andrew Davies

16/04/15 version 0.1: Original version
06/12/16 version 0.2: Added compatability with ESP8266
					  Added support for uOLED displays in I2C mode
					  Added support for WeMos D1 mini OLED shield (see item HCWEMO0007)
					  Made speed improvement to erase function (thanks to vladyslav-savchenko)
22/05/17 version 0.3: Added support for 128x32 OLED display (see items HCMODU0118 & HCMODU0119)

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
#include <Wire.h>
#include "Arduino.h"

#if !defined (ESP8266)
#include <avr/pgmspace.h>
#endif

extern const PROGMEM byte Terminal_8pt[];
extern const PROGMEM byte MedProp_11pt[];
extern const PROGMEM byte LCDLarge_24pt[];

/* Supported displays */
#define SSD1307 0
#define SSD1306 0
#define SH1106 1
#define WEMOS_D1_MINI_OLED 2
#define SSD1306_128_32 3

/* Display settings */
#define SSD1306_RES_X 128
#define SSD1306_RES_Y 64
#define SSD1306_GRAM_COL_START 0x00
#define SSD1306_GRAM_COL_END 0x7F
#define SSD1306_GRAM_PAGE_START 0
#define SSD1306_GRAM_PAGE_END 7
 
#define SH1106_RES_X 128 
#define SH1106_RES_Y 64
#define SH1106_GRAM_COL_START 0x02
#define SH1106_GRAM_COL_END 0x7F
#define SH1106_GRAM_PAGE_START 0
#define SH1106_GRAM_PAGE_END 7

#define WEMOS_RES_X 64
#define WEMOS_RES_Y 48
#define WEMOS_GRAM_COL_START 0x20
#define WEMOS_GRAM_COL_END 0x5F
#define WEMOS_GRAM_PAGE_START 2
#define WEMOS_GRAM_PAGE_END 7

#define SSD1306_128_32_RES_X 128
#define SSD1306_128_32_RES_Y 32
#define SSD1306_128_32_GRAM_COL_START 0x00
#define SSD1306_128_32_GRAM_COL_END 0x7F
#define SSD1306_128_32_GRAM_PAGE_START 0
#define SSD1306_128_32_GRAM_PAGE_END 7



/* Display resolution */
#define BUFFERCOLSIZE 128
#define BUFFERROWSIZE 8

/* Display command register addresses */
#define COLLOWADD 0x00
#define COLHIGHADD 0x10
#define MEMORYADDRESSMODE 0x20
#define SETCOLADDRESS 0x21
#define SETPAGEADDRESS 0x22
#define CHARGEPUMP 0x8D
#define SETMUXRATIO 0xA8
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
#define ENABLECHARGEPUMP 0x14
#define HORIZONTALADDRESSMODE 0x00

/* Hardware interface type */
#define INT_SPI 0
#define INT_I2C 1

/* I2C control byte command / data modes */
#define I2C_COMMAND 0b00000000
#define I2C_DATA 0b01000000

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
  HCuOLED(byte DisplayType, byte I2C_Add, byte RST_DIO = 0xFF);
  void Reset(void);
  void Refresh(void);
  static void ClearBuffer(void);
  //void ClearDisplayRam(void);
  void Flip_H(void);
  void Flip_V(void);
  static void Bitmap(uint8_t Cols, uint8_t ByteRows, const uint8_t BitmapData[]);
  static void Cursor(uint8_t X, uint8_t Y);
  static void Print(char TextString[]);
  static void Print(long Value);
  static void Print(int long Value, byte DecimalPlaces);
  static void Print(float value, byte digits, byte DecimalPlaces);
  static void SetFont(const byte *Font);
  static void Plot(uint8_t X, uint8_t Y);
  static void Line(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
  static void Rect(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t FillMode);
  static void Erase(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2);
  static void DrawMode(byte DrawMode);

  
  private:
  void _CommandMode(void);
  void _DisplayMode(void);
  static void _WriteChar(char character);
  void _Send_Command(byte Data);
  byte _SS;
  byte _DC;
  byte _RST;
  byte _I2C_Add;
  boolean _Interface;
  boolean _V_Ori;
  boolean _H_Ori;
  static byte _XPos;
  static byte _YPos;
  static const byte *_FontType;
  static const uint16_t *_FontDescriptor;
  static byte _FontHight;
  //byte _DisplayRAMColSize; 
  static byte _DrawMode;
  byte _Res_Max_X;
  byte _Res_Max_Y;
  byte _GRAM_Col_Start;
  byte _GRAM_Col_End;
  byte _GRAM_Page_Start;
  byte _GRAM_Page_End;
  byte _RAM_Pages;
  byte _DisplayType;
}; 

#endif
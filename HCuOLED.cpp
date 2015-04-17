/* FILE:    HCuOLED.cpp
   DATE:    16/04/15
   VERSION: 0.1
   AUTHOR:  Andrew Davies

16/04/15 version 0.1: Original version

Library for SSD1307 and SH1106 based OLED displays. In particular this library has been 
written for the following displays:

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


#include "HCuOLED.h"
#include "Arduino.h"
#include <avr/pgmspace.h>
#include "fonts.h"

/* Display output buffer */
byte DisplayBuffer[BUFFERCOLSIZE][8];


/* Variables and pointer used by shared static member functions */
byte HCuOLED::_XPos;
byte HCuOLED::_YPos;
byte HCuOLED::_DrawMode;
const byte *HCuOLED::_FontType;
const unsigned int *HCuOLED::_FontDescriptor;
byte HCuOLED::_FontHight;


/* Constructor to initialise the GPIO and library */
HCuOLED::HCuOLED(byte DisplayType, byte SS_DIO, byte DC_DIO, byte RST_DIO)
{
  /* Set the slave select (SS), Data/Command mode (DC) and reset (RST) pins to outputs */
  _SS = SS_DIO;
  _DC = DC_DIO;
  _RST = RST_DIO;

   pinMode(_SS, OUTPUT);   
   pinMode(_DC, OUTPUT);  
   pinMode(_RST, OUTPUT); 
  
  
  /* Enable the hardware SPI interface */
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  /* Set vertical and horizontal orientation of the display */
  _V_Ori = 0;
  _H_Ori = 0;

  /* Set dimension and display area of the screen */
  switch(DisplayType)
  {
	case SSD1307:
	  _StartCol = 0;
	  _DisplayRAMColSize = 128;
	  break;
	
	case SH1106:
	  _StartCol = 2;
	  _DisplayRAMColSize = 132;
	  break;  
  }
	
  /* Set text cursor to top corner */  
  Cursor(0, 0);
  
  /* Set default font */
  SetFont(Terminal_8pt);  
  
  /* Set default draw mode */
  DrawMode(NORMAL);

}


/* Writes the contents of the display buffer to the display */
void HCuOLED::Refresh(void)
{
  byte ColIndex;
  byte RowIndex;   
      
  for (RowIndex = 0; RowIndex < 8; RowIndex++)
  {
    digitalWrite(_DC, LOW);
    /* Page address */
    digitalWrite(_SS, LOW);
    SPI.transfer(PAGEADD | RowIndex);
    digitalWrite(_SS, HIGH);
    
    /* Lower column address */
    digitalWrite(_SS, LOW);
    SPI.transfer(COLLOWADD | _StartCol);
    digitalWrite(_SS, HIGH);
  
    /* Higher column address */
    digitalWrite(_SS, LOW);
    SPI.transfer(COLHIGHADD | 0x0); 
    digitalWrite(_SS, HIGH);
   
    /* Write to display RAM */  
	_DisplayMode();
    for (ColIndex = 0; ColIndex < BUFFERCOLSIZE; ColIndex++)
    {
      digitalWrite(_SS, LOW); 
      SPI.transfer(DisplayBuffer[ColIndex][RowIndex]);
      digitalWrite(_SS, HIGH); 
    }
  }
}


/* Reset and initialise the module */
void HCuOLED::Reset(void)
{
  /* Wait 100mS for DC-DC to stabilise. This can probably be reduced */
  delay(100);
  
  /* Reset the module */
  digitalWrite(_RST, LOW);
  delay(1);
  digitalWrite(_RST, HIGH);
  

  /* Enable charge pump on SSD1306 */
  digitalWrite(_SS, LOW);
  SPI.transfer(0x8D);
  SPI.transfer(0x14);
  digitalWrite(_SS, HIGH);
  
  /* Clear the display buffer */
  ClearBuffer();

  /* Output the display buffer to clear the display RAM */
  //ClearDisplayRam();
  Refresh();
  
  /* Change to command mode */
  _CommandMode();
  
  /* Turn the display on */
  digitalWrite(_SS, LOW);
  SPI.transfer(DISPLAYONADD | 1);
  digitalWrite(_SS, HIGH);
  
  /* Wait 150mS for display to turn on */
  delay(150);
  
  /* Flip the display */
  Flip_H();
  Flip_V();
}

/* Clears the contents of the output buffer */
void HCuOLED::ClearBuffer(void)
{
  byte ColIndex;
  byte RowIndex;

  for (RowIndex = 0; RowIndex < 8; RowIndex++)
  {    
    for (ColIndex = 0; ColIndex < BUFFERCOLSIZE; ColIndex++)
    {
      DisplayBuffer[ColIndex][RowIndex] = 0x00;
    }
  }
}



// void HCuOLED::ClearDisplayRam(void)
// {
  // byte ColIndex;
  // byte RowIndex;   
      
  // for (RowIndex = 0; RowIndex < 8; RowIndex++)
  // {
    // digitalWrite(_DC, LOW);
    // /* Page address */
    // digitalWrite(_SS, LOW);
    // SPI.transfer(PAGEADD | RowIndex);
    // digitalWrite(_SS, HIGH);
    
    // /* Lower column address */
    // digitalWrite(_SS, LOW);
    // SPI.transfer(COLLOWADD | _StartCol);
    // digitalWrite(_SS, HIGH);
  
    // /* Higher column address */
    // digitalWrite(_SS, LOW);
    // SPI.transfer(COLHIGHADD | 0x0); 
    // digitalWrite(_SS, HIGH);
      
    // digitalWrite(_DC, HIGH);   
    // for (ColIndex = 0; ColIndex < _DisplayRAMColSize; ColIndex++)
    // {
      // digitalWrite(_SS, LOW); 
      // SPI.transfer(0x00);
      // digitalWrite(_SS, HIGH); 
    // }
  // }
// }


/* Switch to command mode */
void HCuOLED::_CommandMode(void)
{
   digitalWrite(_DC, LOW);  
}

/* Switch to display mode */
void HCuOLED::_DisplayMode(void)
{
   digitalWrite(_DC, HIGH);  
}


/* Flip the horizontal orientation of the screen */
void HCuOLED::Flip_H(void)
{
  _CommandMode();
  digitalWrite(_SS, LOW);
  _H_Ori = ~_H_Ori;
  if(_H_Ori)
  {
    SPI.transfer(SCANDIRECTIONADD | SCANDIRREVERSE);
  }else
  {
    SPI.transfer(SCANDIRECTIONADD | SCANDIRNORMAL);
  }
  digitalWrite(_SS, HIGH);
}

/* Flip the vertical orientation of the screen */
void HCuOLED::Flip_V(void)
{
  _CommandMode();
  digitalWrite(_SS, LOW);
  _V_Ori = ~_V_Ori;
  if(_V_Ori)
  {
    SPI.transfer(SEGMENTMAPADD | SEGMENTMAPREVERSE);
  }else
  {
    SPI.transfer(SEGMENTMAPADD | SEGMENTMAPNORMAL);
  }
  digitalWrite(_SS, HIGH);
}



/* Write bitmap data to the LCD starting at the cursor location where:
   Cols is the number byte columns to write to.
   ByteRows is the number of rows to write to in 8 pixel chunks 
   BitmapData is an array containing the bitmap data to be written */

void HCuOLED::Bitmap(byte Cols, byte ByteRows, const byte BitmapData[])
{
  byte XIndex;
  byte YIndex;
  
  byte BufRow;
  byte BufX;
  unsigned int BitmapIndex;
  
  /* Step through each 8 pixel row */
  for (YIndex = 0; YIndex < ByteRows; YIndex++)
  {
	/* Step through each column */
    for (XIndex = 0; XIndex < Cols; XIndex++)
    {
      BufX = XIndex + _XPos;
      
      /* If column is beyond display area then don't bother writing to it*/
      if(BufX < BUFFERCOLSIZE)
      {
        BufRow = YIndex + (_YPos / 8);
        BitmapIndex = (YIndex * Cols)+ XIndex;
      
        /* If row is beyond the display area then don't bother writing to it */
		if(BufRow < BUFFERROWSIZE)
          if (_DrawMode == NORMAL)
		  {
		    DisplayBuffer[BufX][BufRow] |= pgm_read_byte_near(&BitmapData[BitmapIndex]) << (_YPos%8);
		  }else
		  {
		    DisplayBuffer[BufX][BufRow] ^= pgm_read_byte_near(&BitmapData[BitmapIndex]) << (_YPos%8);
		  }

		/* If column data overlaps to 8 bit rows then write to the second row */  
        if(_YPos%8 && (BufRow +1) < BUFFERROWSIZE)
          if (_DrawMode == NORMAL)
		  {
 		    DisplayBuffer[BufX][BufRow+1] |= pgm_read_byte_near(&BitmapData[BitmapIndex]) >> (8 - (_YPos%8));
		  }else
		  {
 		    DisplayBuffer[BufX][BufRow+1] ^= pgm_read_byte_near(&BitmapData[BitmapIndex]) >> (8 - (_YPos%8));		  
		  }
      }
    }
  }
}


/* Write to a single pixel on the display where:
   X is the x axis coordinate of the pixel
   Y is the Y axis coordinate of the pixel */
void HCuOLED::Plot(byte X, byte Y)
{
  byte row = Y / BUFFERROWSIZE;

  if(X < BUFFERCOLSIZE && row < BUFFERROWSIZE)
    if (_DrawMode == NORMAL)
	{
	  DisplayBuffer[X][row] |=  (0x01 << (Y % 8));
	}else if(_DrawMode == INVERT)
	{
	  DisplayBuffer[X][row] ^=  (0x01 << (Y % 8));	
	}else if(_DrawMode == CLEAR)
	{
	  DisplayBuffer[X][row] &=  ~(0x01 << (Y % 8));	
	}
}


/* Draw a line where:
   X1 is the starting X axis coordinate of the line
   Y1 is the starting Y axis coordinate of the line
   X2 is the starting X axis coordinate of the line
   Y2 is the starting Y axis coordinate of the line */
void HCuOLED::Line(byte X1, byte Y1, byte X2, byte Y2)
{
  double step;
  int x, y;
 
  /* If start coordinates are below and to the right of the end coordinate then flip them */
  if((X2 <= X1 && Y2 <= Y1) || (X2 >= X1 && Y1 >= Y2) || (X2 >= X1 && Y1 >= Y2)) 
  {
    X2^=X1;
    X1^=X2;
    X2^=X1;
    Y2^=Y1;
    Y1^=Y2;
    Y2^=Y1;
  }

  /* If X axis is wider than Y axis then step though X axis */
  if(((X2-X1) >= (Y2-Y1)) || ((X1 - X2) >= (Y2-Y1)))
  {
   	step = (double)(Y2-Y1) / (X2-X1);
    if(X2 >= X1 && Y2 >= Y1)
    {
	  for(x = X1; x <= X2; x++)
	    Plot(x, ((x-X1) * step) + Y1); 
    }else
    {
	  for(x = X1; x >= X2; x--)
	    Plot(x, Y2 + ((x-X2) * step));
    } 
  }else /* If Y axis is wider than X axis then step though Y axis */
  {
  	step = (double)(X2-X1) / (Y2-Y1);
    if(Y2 >= Y1 && X2 >= X1)
    {
	  for(y = Y1; y <= Y2; y++)
	    Plot(((y-Y1) * step) + X1, y); 
    }else
	{
	  for(y = Y2; y >= Y1; y--)
	    Plot(X2 + ((y-Y2) * step),y);	
	}
  }
}

/* Draw a rectangle where:
   X1 is the X axis coordinate of the first corner
   Y1 is the Y axis coordinate of the first corner
   X2 is the X axis coordinate of the opposite corner
   Y2 is the Y axis coordinate of the opposite corner 
   FillMode is sets the drawing mode for the rectangle. Options are:
   OUTLINE (Draws an outlined rectangle with no fill
   SOLID (Draws a filled filled rectangle) */
   
void HCuOLED::Rect(byte X1, byte Y1, byte X2, byte Y2, byte FillMode)
{
  byte y;

  /* Draw the top and bottom borders */
  Line(X1, Y1, X2, Y1);
  Line(X1, Y2, X2, Y2);
  
  /* If first corner is below second corner then flip the coordinates */
  if(Y1 > Y2)
  {
     Y2^=Y1;
     Y1^=Y2;
     Y2^=Y1;  
  }
  
  /* If rectangle is wider than two pixels set Y for drawing vertical borders */
  if(Y2-Y1 > 1)
  {
	Y1++;
	Y2--;
  }
 
  /* If box is solid then fill area between top and bottom border */
  if(FillMode == SOLID)
  {
	for(y = Y1; y <= Y2; y++)
	  Line(X1, y, X2, y);
  }else  /* if not solid then just draw vertical borders */
  {
    Line(X1, Y1, X1, Y2);
    Line(X2, Y1, X2, Y2); 
  }
}

/* Clears an area of the display buffer where:
   X1 is the X axis coordinate of the first corner
   Y1 is the Y axis coordinate of the first corner
   X2 is the X axis coordinate of the opposite corner
   Y2 is the Y axis coordinate of the opposite corner */
void HCuOLED::Erase(byte X1, byte Y1, byte X2, byte Y2)
{
  byte temp = _DrawMode;
  _DrawMode = CLEAR;
  Rect(X1, Y1, X2, Y2, SOLID);
  _DrawMode = temp;
}

/* Sets the drawing mode for text and graphics where:
   DrawMode sets the drawing mode. Options are:
   NORMAL (Pixels are set to foreground colour) 
   INVERT (Pixels are set to the opposite of their current state) 
   CLEAR  (Pixels are set to background colour) */
void HCuOLED::DrawMode(byte DrawMode)
{
  _DrawMode = DrawMode;
}

/* Sets the location of the cursor for text and bitmap graphics where:
   X and Y are the starting top left X & Y axis coordinates */

void HCuOLED::Cursor(byte X, byte Y)
{
  _XPos = X;
  _YPos = Y;
}


/* Print a text string to the LCD starting at the cursor coordinates where:
   TextString[] is a string array containing the text to be displayed */
void HCuOLED::Print(char TextString[])
{
  byte StringLength;
  byte Index;
  
  /* Finds length of string */
  StringLength = strlen(TextString) - 1;

  for (Index = 0; Index <= StringLength; Index++)
  {
	_WriteChar(TextString[Index] - 32);
  }
}


/* Print a floating point number to the LCD starting at the cursor coordinates where:
   value is the floating point value to display (max 10 digits including decimal places)
   digits is the number of digits to crop the number to (including decimal places)
   DecimalPlaces is the number of decimal places to display */
   
void HCuOLED::Print(float value, byte digits, byte DecimalPlaces)
{
  char Buffer[10];
  
  /* Clip the number of digits to 10 */
  if (digits > 10)
   digits = 10;

  /* Convert the value to an character array */ 
  dtostrf(value, digits, DecimalPlaces, Buffer);
  
  /* Output the array to the display buffer */
  Print(Buffer);
}


/* Print a signed integer number to the LCD at the current cursor 
   coordinates where:
   Value is signed integer number of type long */
void HCuOLED::Print(long Value)
{
  byte Digits[10];
  int long Temp;
  byte NumDigits = 0;
  
  /* Is the number negative ? */
  if (Value < 0)
  {
	_WriteChar(13);
	Temp = Value * -1;
  }else
  {
    Temp = Value;
  }
  
  /* Store each digit in a byte array so that they 
     can be printed in reverse order */
  while (Temp)
  {
    Digits[NumDigits] = Temp % 10;
	Temp /= 10;
	NumDigits++;
  } 

  /* Print each digit */
  while(NumDigits)
  {
	NumDigits--;
	_WriteChar(Digits[NumDigits] + 16);
  }
}


/* Print a signed integer number with decimal point to the LCD at 
   the current cursor coordinates where:
   Value is signed integer number of type long
   DecimalPlaces is the position of the decimal point */
void HCuOLED::Print(int long Value, byte DecimalPlaces)
{
  byte Digits[10];
  int long Temp;
  byte NumDigits = 0;
  
  /* Is the number negative ? */
  if (Value < 0)
  {
	_WriteChar(13); 
	Temp = Value * -1;
  }else
  {
    Temp = Value;
  }
  
  /* Store each digit in a byte array so that they 
     can be printed in reverse order */
  while (Temp)
  {
    Digits[NumDigits] = Temp % 10;
	Temp /= 10;
	NumDigits++;
  } 

  /* If the decimal point is at the beginning of the 
     number then pad it with a zero */ 
  if(DecimalPlaces == NumDigits)
  {
    _WriteChar(16);
  }
  
  /* Print each digit */
  while(NumDigits)
  {
	NumDigits--;
	if (NumDigits + 1 == DecimalPlaces)
	  _WriteChar(14);
	
	_WriteChar(Digits[NumDigits] + 16);
  }
}


/* Write a single character or digit at the current cursor coordinate */
void HCuOLED::_WriteChar(char character)
{
    const byte *FontByteAddress;
    int FontWidth;
	
	FontByteAddress = _FontType + pgm_read_word_near(_FontDescriptor + (character * 2) + 1);
	FontWidth = pgm_read_word_near(_FontDescriptor + (character * 2));
	Bitmap(FontWidth, _FontHight, FontByteAddress);  
	_XPos = _XPos + FontWidth + 2;
}


/* Sets the font to be used when writing text or numbers where:
   *Font is the font type to be used. Options are:
   Terminal_8pt (A small 8x8 fixed width font)
   MedProp_11pt (A medium two row proportional font)
   LCDLarge_24pt (A large 4 row LCD style font) */
void HCuOLED::SetFont(const byte *Font)
{
  if(Font == Terminal_8pt)
  {
    _FontType = Terminal_8pt;
	_FontHight = Terminal_8ptFontInfo.CharacterHeight;
	_FontDescriptor = Terminal_8ptFontInfo.Descriptors;
  }else if(Font == MedProp_11pt)
  {
    _FontType = MedProp_11pt;
	_FontHight = MedProp_11ptFontInfo.CharacterHeight;
	_FontDescriptor = MedProp_11ptFontInfo.Descriptors;
  }else if(Font == LCDLarge_24pt  )
  {
    _FontType = LCDLarge_24pt;
	_FontHight = LCDLarge_24ptFontInfo.CharacterHeight;
	_FontDescriptor = LCDLarge_24ptFontInfo.Descriptors;
  }
}
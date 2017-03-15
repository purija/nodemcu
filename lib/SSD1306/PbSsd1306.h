#ifndef PBSSD1306_H
#define PBSSD1306_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initDisplay(void);
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);
void testdrawchar(void);
void testdrawcircle(void);
void testfillrect(void);
void testdrawtriangle(void);
void testfilltriangle(void);
void testdrawroundrect(void);
void testfillroundrect(void);
void testdrawrect(void);
void testdrawline(void);
void testscrolltext(void);
void testDisplay(void);
void printText(const String& text);
void clearDisplay(void);
void printTextWithouClearing(const String& text, const int& cursorX, const int& cursorY);


#endif

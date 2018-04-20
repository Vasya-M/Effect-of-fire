#ifndef WG_H_INCLUDED
#define WG_H_INCLUDED

//#include <stdio.h>
#include <math.h>
#ifdef __linux__
    #include <stdlib.h>
#elif _WIN32
    #include <Windows.h>
    #include <wingdi.h>

#endif
#define RED 0xFF
#define GREEN 0xFF00
#define BLUE 0xFF0000
#define BLACK 0
#define RGB(red,green,blue) ( blue<<16|green<<8|red)
#define GET_RED(color) (color &0xff)
#define GET_GREEN(color) ((color>>8)&0xff)
#define GET_BLUE(color) ((color>>16)&0xff)

typedef void (*myfunc)();

void init_WinGraphic(char* title,int width,int  height);
void runWindows();
void setDrawFunction(int time, myfunc );
void drawRectangle(int x1,int y1,int x2,int y2);
void drawRectangle(int x1,int y1,int x2,int y2,int color);
void setpixel(int x,int y,int color);
unsigned int getpixel(int x ,int y);
void setpixelR(int x,int y,unsigned char color);
void setpixelG(int x,int y,unsigned char color);
void setpixelB(int x,int y,unsigned char color);
unsigned char getpixelR(int x ,int y);
unsigned char getpixelG(int x ,int y);
unsigned char getpixelB(int x ,int y);

void line(int x1,int y1,int x2,int y2);
void line(int x1,int y1,int x2,int y2,int color);
void line(int x1,int y1,int x2,int y2,int clolor, int width);
void setColorPenProperty(int color,int width);
void setColorBrushProperty(int color);
void Clear();
#endif // WG_H_INCLUDED

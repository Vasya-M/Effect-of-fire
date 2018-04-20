#include "WG.h"
#define WHITE 0xffffff
HWND hwnd;
HINSTANCE hin;
HBITMAP hbit;
HDC hdc, hdc_win;

myfunc ffunc;
int istime_=0;
int wtime=1;
int w_img,h_img;
void* pmem_img=0;
int FScanLineSize;

int color_brush=WHITE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void Clear()
{
    if (color_brush != WHITE )
    {
		HBRUSH col;
		HGDIOBJ oldCol;
		col = CreateSolidBrush(WHITE);
        oldCol = SelectObject(hdc,col);
		Rectangle(hdc, 0, 0, w_img, h_img);
		SelectObject(hdc, oldCol);
		DeleteObject(col);
    }
	Rectangle(hdc, 0, 0, w_img, h_img);

}

void line(int x1,int y1,int x2,int y2)
{
    MoveToEx(hdc,x1,y1,0);
    LineTo(hdc,x2,y2);
}

void setColorBrushProperty(int color)
{
    HBRUSH col = CreateSolidBrush(color);
    DeleteObject(SelectObject(hdc,col));
    color_brush = color;
}

void setColorPenProperty(int color,int width)
{
    HPEN newpen = CreatePen(PS_SOLID,width,color);
    DeleteObject(SelectObject(hdc,newpen));
}

void line(int x1,int y1,int x2,int y2,int color)
{
    HPEN newpen = CreatePen(PS_SOLID,1,color);
    HGDIOBJ oldPen = SelectObject(hdc,newpen);
    line(x1,y1,x2,y2);
    SelectObject(hdc,oldPen);
    DeleteObject(newpen);
}

void line(int x1,int y1,int x2,int y2,int color, int width)
{
    HPEN newpen = CreatePen(PS_SOLID,width,color);
    HGDIOBJ oldPen = SelectObject(hdc,newpen);
    line(x1,y1,x2,y2);
    SelectObject(hdc,oldPen);
    DeleteObject(newpen);
}

void setpixelR(int x,int y,unsigned char color)
{
    char *p=(char*)((char*)pmem_img+(y*FScanLineSize)+x*3);
    *(p+2)=color;
}

void setpixelG(int x,int y,unsigned char color)
{
    char *p=(char*)((char*)pmem_img+(y*FScanLineSize)+x*3);
    *(p+1)=color;
}
void setpixelB(int x,int y,unsigned char color)
{
    char *p=(char*)((char*)pmem_img+(y*FScanLineSize)+x*3);
    *(p+0)=color;
}


void setpixel(int x,int y,int color)
{
    unsigned char *p=(unsigned char*)((unsigned char*)pmem_img+(y*FScanLineSize)+x*3);
    *(p+2) = color&0xff;
    *(p+1) = (color>>8)&0xff;
    *(p+0) = (color>>16)&0xff;
}

unsigned char getpixelR(int x,int y)
{
    unsigned char *p=(unsigned char*)((unsigned char*)pmem_img+(y*FScanLineSize)+x*3);
    return *(p+2);
}

unsigned char getpixelG(int x,int y)
{
    unsigned char *p=(unsigned char*)((unsigned char*)pmem_img+(y*FScanLineSize)+x*3);
    return *(p+1);
}
unsigned char getpixelB(int x,int y)
{
    unsigned char *p=(unsigned char*)((unsigned char*)pmem_img+(y*FScanLineSize)+x*3);
    return *(p);
}

unsigned int getpixel(int x,int y)
{
    unsigned char *p=(unsigned char*)((unsigned char*)pmem_img+(y*FScanLineSize)+x*3);
    return (unsigned int)((*(p+0)<<16)|(*(p+1)<<8)|(*(p+2)));
}


void drawRectangle(int x1,int y1,int x2,int y2)
{
    Rectangle(hdc,x1,y1,x2,y2);
}

void drawRectangle(int x1,int y1,int x2,int y2,int color)
{
    HBRUSH col = CreateSolidBrush(color);
    HGDIOBJ oldCol = SelectObject(hdc,col);
    Rectangle(hdc,x1,y1,x2,y2);
    SelectObject(hdc,oldCol);
    DeleteObject(col);
}


void freeCanvas()
{
    DeleteDC(hdc);
    DeleteObject(hbit);
}
void createCanvas(int w,int h)
{
    w_img = w;
    h_img = h;
    HDC loc= GetDC(0);
    hdc = CreateCompatibleDC(loc);
    BITMAPINFO info;
    char*p= (char*)&info;// life hack, clear struct ;)
    int i=sizeof(BITMAPINFO);
    while(i--)
        *p++=0;
    info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth=w;
	info.bmiHeader.biHeight=-h;
	info.bmiHeader.biPlanes=1;
	info.bmiHeader.biBitCount=24;
	info.bmiHeader.biCompression=BI_RGB;
	info.bmiHeader.biSizeImage=h*w*3;
    hbit = CreateDIBSection(loc,&info,DIB_RGB_COLORS,&pmem_img,0,0);
    SelectObject(hdc,hbit);
    setColorBrushProperty(WHITE);
    Rectangle(hdc,0,0,w,h);
    ReleaseDC(0,loc);
    FScanLineSize = ((info.bmiHeader.biBitCount * w +31) >> 3) & 0x0FFFFFFFC;
}




VOID CALLBACK TimerProc( HWND hwnd, UINT uMsg,UINT idEvent,DWORD dwTime)
{

    if (istime_) ffunc();

    BitBlt(hdc_win,5,5,w_img,h_img,hdc,0,0,SRCCOPY);

}

void setDrawFunction(int time, myfunc funtion)
{
    istime_=1;
    wtime=time;
    ffunc=funtion;
    KillTimer(hwnd,12);
    SetTimer(hwnd,12,wtime,&TimerProc);
}

void runWindows()
{
    MSG msg;
    while(1)
    {
        if(!GetMessage(&msg,NULL,0,0)) break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void init_WinGraphic(char * title, int width, int height)
{
    WNDCLASSEX wc;

    char ClassName[]="my windows";
    hin=GetModuleHandle(NULL);

    wc.cbSize=sizeof(WNDCLASSEX);
	wc.style=CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc= WndProc;
	wc.cbClsExtra=NULL;
	wc.cbWndExtra=NULL;
	wc.hInstance=hin;
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=ClassName;
	HICON hIcon =  LoadIcon(NULL,IDI_QUESTION);
    wc.hIcon=hIcon;
    wc.hIconSm=hIcon;
    RegisterClassEx(&wc);
    hwnd= CreateWindowEx(NULL,ClassName,title,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,
           CW_USEDEFAULT,width,height,NULL,NULL,hin,NULL);
    hdc_win = GetDC(hwnd);
    createCanvas(width-27,height-50);
    ShowWindow(hwnd,SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {

		case WM_CREATE:
			  SetTimer(hwnd,12,wtime,&TimerProc);
			break;
		case WM_DESTROY:
			KillTimer(hwnd,12);
			ReleaseDC(hwnd,hdc_win);
			freeCanvas();
			PostQuitMessage(NULL);
			break;

		default :
			return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}

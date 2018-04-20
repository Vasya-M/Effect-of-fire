#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include "WG.h"
#define W WF-50
#define H HF-50
#define PAL 900

#define WF 600 // widht
#define HF 250// height
void print(void);
int what(int x, int y);
void Null(int flag);
typedef struct MyStruct
{
	short	int r, g, b;
}RgB;
RgB palette[PAL], nul;
int  map[H][W];

double start, ends;

void generatePalette(void);
int average(int sum);
int is = 0;

int s = 0, b = 100;
int main()
{
	init_WinGraphic("KG", WF, HF);
	srand(time(0));
	generatePalette();
	Null(0);
	setDrawFunction(100, &print);
	runWindows();
	return 0;
}

void print(void)
{
	//start = clock();
	Null(1);
	int Height = H;
	for (int i = 0; i < 4; i++)

		for (size_t y = 0; y < H - 2; y++)
		{
			for (size_t x = 0; x < W; x++)
				map[y][x] = what(x, y);
		}
	for (size_t y = 0; y < H - 6; y++)
		for (size_t x = 0; x < W; x++)
		{
			setpixel(x, y, RGB(palette[map[y][x]].r, palette[map[y][x]].g, palette[map[y][x]].b));
		}
	//ends = clock();
	//printf("\n time %lf \n", (ends - start) / 1000);
}

int RR(void)
{
	int color;
	while (1)
	{
		color = rand() % PAL;
		if (color > PAL - 20)return color;
	}
}

void Null(int flag)
{
	for (size_t y = 0; y < H; y++)
		for (size_t x = 0; x < W; x++)
			if (y > H - 3 && (x > 30 && x < W - 50))
			{
				if (!(rand() % 4 == 0))
					map[y][x] = RR();
				else map[y][x] = 0;

			}
			else if (!flag)map[y][x] = 0;
}



int what(int x, int y)
{
	s++;
	if (s > 1000000)
	{
		b++;
		s = 0;
	}
	int sum = 0;
	sum += map[y][x];
	y++;
	if (x - 1 > 0)
		sum += map[y][x - 1];
	else sum += 0;
	if (x + 1 < W)
		sum += map[y][x + 1];
	else  sum += 0;
	sum += map[y++][x];
	sum += map[y][x];

	sum = sum / 5;
	//sum = average(sum);
	sum += (sum - PAL - (H - y)) / b;



	if (sum < 0)
		sum = 0;

	return sum;
}
int average(int sum)
{
	if (sum)
		sum = (sum / 10) * 10;
	return sum;
}

void generatePalette()
{

	for (size_t i = 0; i < PAL; i++)
	{
		RgB buf = nul;
		if (i <= PAL)
		{
			palette[i].r = i * ((double)255 / (PAL / 3));
		}
		if (i > (PAL / 3) && i <= (PAL * 2 / 3))
		{
			palette[i].r = 255;
			palette[i].g = ((double)160 / (PAL / 3))*(i - (PAL / 3));
		}
		if (i > (PAL * 2 / 3))
		{
			palette[i].r = 255;
			palette[i].g = (((double)95 / (PAL / 3))*(i - (PAL * 2 / 3))) + 160;
			palette[i].b = ((double)255 / (PAL / 3))*(i - (PAL * 2 / 3));
		}
	}
}


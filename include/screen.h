#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stddef.h>

typedef uint8_t u8;

typedef struct
{
    u8 r, g, b;
} Pixel;

typedef struct
{
    int width, height;
    Pixel *pixels;
} Screen;

Screen *ScreenCreate(int width, int height);
void ScreenDestroy(Screen **screen);

void ScreenClear(Screen *screen, Pixel color);
void ScreenSetPixel(Screen *screen, int x, int y, Pixel color);

void ScreenRender(const Screen *screen);

void ScreenFill(Screen *screen, int x, int y, int width, int height, Pixel color);
void ScreenDrawLine(Screen *screen, int x0, int y0, int x1, int y1, Pixel color);
void ScreenDrawCircleOutline(Screen *screen, int cx, int cy, int radius, Pixel color);

#endif
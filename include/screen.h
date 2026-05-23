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
    size_t width, height;
    Pixel *pixels;
} Screen;

Screen *ScreenCreate(size_t width, size_t height);
void ScreenDestroy(Screen **screen);

void ScreenClear(Screen *screen, Pixel color);
void ScreenSetPixel(Screen *screen, size_t x, size_t y, Pixel color);

void ScreenRender(const Screen *screen);

void ScreenFill(Screen *screen, size_t x, size_t y, size_t width, size_t height, Pixel color);
void ScreenDrawLine(Screen *screen, size_t x0, size_t y0, size_t x1, size_t y1, Pixel color);

#endif
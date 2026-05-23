#include "screen.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

Screen *ScreenCreate(int width, int height)
{
    if (width <= 0 || height <= 0)
        return NULL;

    Screen *screen = malloc(sizeof(Screen));
    if (!screen)
        return NULL;

    size_t pixel_count = (size_t)width * (size_t)height;

    Pixel *pixels = malloc(pixel_count * sizeof(Pixel));
    if (!pixels)
    {
        free(screen);
        return NULL;
    }

    screen->width = width;
    screen->height = height;
    screen->pixels = pixels;

    memset(screen->pixels, 0, pixel_count * sizeof(Pixel));

    return screen;
}

void ScreenDestroy(Screen **screen)
{
    if (screen && *screen)
    {
        free((*screen)->pixels);
        free(*screen);
        *screen = NULL;
    }
}

void ScreenClear(Screen *screen, Pixel color)
{
    if (!screen)
        return;

    for (int row = 0; row < screen->height; row++)
        for (int col = 0; col < screen->width; col++)
            screen->pixels[row * screen->width + col] = color;
}

void ScreenSetPixel(Screen *screen, int x, int y, Pixel color)
{
    if (!screen)
        return;

    if (x < 0 || y < 0)
        return;

    if (x >= screen->width || y >= screen->height)
        return;

    screen->pixels[y * screen->width + x] = color;
}

void ScreenRender(const Screen *screen)
{
    if (!screen)
        return;

    printf("\033[2J\033[H");

    for (int row = 0; row < screen->height; row++)
    {
        for (int col = 0; col < screen->width; col++)
        {
            Pixel pixel = screen->pixels[row * screen->width + col];
            printf("\033[48;2;%d;%d;%dm  \033[0m", pixel.r, pixel.g, pixel.b);
        }

        printf("\033[0m\n");
    }

    fflush(stdout);
}

void ScreenFill(Screen *screen, int x, int y, int width, int height, Pixel color)
{
    for (int row = y; row < y + height; row++)
        for (int col = x; col < x + width; col++)
            ScreenSetPixel(screen, col, row, color);
}

void ScreenDrawLine(Screen *screen, int x0, int y0, int x1, int y1, Pixel color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (1)
    {
        ScreenSetPixel(screen, x0, y0, color);

        int e2 = 2 * error;

        if (e2 >= dy)
        {
            if (x0 == x1)
                break;

            error = error + dy;
            x0 = x0 + sx;
        }

        if (e2 <= dx)
        {
            if (y0 == y1)
                break;

            error = error + dx;
            y0 = y0 + sy;
        }
    }
}

void ScreenDrawCircleOutline(Screen *screen, int cx, int cy, int radius, Pixel color)
{
    if (radius < 0)
        return;

    int t1 = radius / 16;
    int x = radius;
    int y = 0;

    while (x >= y)
    {
        ScreenSetPixel(screen, cx + x, cy + y, color);
        ScreenSetPixel(screen, cx + y, cy + x, color);
        ScreenSetPixel(screen, cx - y, cy + x, color);
        ScreenSetPixel(screen, cx - x, cy + y, color);

        ScreenSetPixel(screen, cx - x, cy - y, color);
        ScreenSetPixel(screen, cx - y, cy - x, color);
        ScreenSetPixel(screen, cx + y, cy - x, color);
        ScreenSetPixel(screen, cx + x, cy - y, color);

        y = y + 1;
        t1 = t1 + y;

        int t2 = t1 - x;

        if (t2 >= 0)
        {
            t1 = t2;
            x = x - 1;
        }
    }
}

void ScreenDrawFilledCircle(Screen *screen, int cx, int cy, int radius, Pixel color)
{
    if (radius < 0)
        return;

    int t1 = radius / 16;
    int x = radius;
    int y = 0;

    while (x >= y)
    {
        for (int i = cx - x; i <= cx + x; i++)
        {
            ScreenSetPixel(screen, i, cy + y, color);
            ScreenSetPixel(screen, i, cy - y, color);
        }

        for (int i = cx - y; i <= cx + y; i++)
        {
            ScreenSetPixel(screen, i, cy + x, color);
            ScreenSetPixel(screen, i, cy - x, color);
        }

        y = y + 1;
        t1 = t1 + y;

        int t2 = t1 - x;

        if (t2 >= 0)
        {
            t1 = t2;
            x = x - 1;
        }
    }
}
#include "screen.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Screen *ScreenCreate(size_t width, size_t height)
{
    Screen *screen = malloc(sizeof(Screen));
    if (!screen)
        return NULL;

    Pixel *pixels = malloc(width * height * sizeof(Pixel));
    if (!pixels)
    {
        free(screen);
        return NULL;
    }

    screen->width = width;
    screen->height = height;
    screen->pixels = pixels;

    memset(screen->pixels, 0, width * height * sizeof(Pixel));

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

    for (size_t row = 0; row < screen->height; row++)
        for (size_t col = 0; col < screen->width; col++)
            screen->pixels[row * screen->width + col] = color;
}

void ScreenSetPixel(Screen *screen, size_t x, size_t y, Pixel color)
{
    if (!screen)
        return;

    if (y >= screen->height || x >= screen->width)
        return;

    screen->pixels[y * screen->width + x] = color;
}

void ScreenRender(const Screen *screen)
{
    if (!screen)
        return;

    printf("\033[H");

    for (size_t row = 0; row < screen->height; row++)
    {
        for (size_t col = 0; col < screen->width; col++)
        {
            Pixel pixel = screen->pixels[row * screen->width + col];
            printf("\033[48;2;%d;%d;%dm  \033[0m", pixel.r, pixel.g, pixel.b);
        }
        printf("\033[0m\n");
    }

    fflush(stdout);
}
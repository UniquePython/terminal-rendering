#include "screen.h"

int main(void)
{
    Screen *screen = ScreenCreate(90, 60);
    if (!screen)
        return 1;

    ScreenClear(screen, (Pixel){255, 255, 255});
    ScreenSetPixel(screen, 45, 30, (Pixel){255, 0, 0});
    ScreenFill(screen, 0, 0, 10, 10, (Pixel){0, 255, 0});
    ScreenDrawLine(screen, 40, 0, 45, 10, (Pixel){0, 0, 255});

    ScreenRender(screen);

    ScreenDestroy(&screen);

    return 0;
}
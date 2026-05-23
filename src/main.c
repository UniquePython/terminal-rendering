#include "screen.h"

#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    Screen *screen = ScreenCreate(80, 40);
    if (!screen)
        return EXIT_FAILURE;

    Pixel background = {0, 0, 0};
    Pixel ball = {255, 0, 0};

    int radius = 4;

    int x = 20;
    int y = 10;

    int vx = 1;
    int vy = 1;

    while (1)
    {
        ScreenClear(screen, background);

        ScreenDrawFilledCircle(screen, x, y, radius, ball);

        ScreenRender(screen);

        x = x + vx;
        y = y + vy;

        if (x - radius < 0)
        {
            x = radius;
            vx = -vx;
        }
        else if (x + radius >= screen->width)
        {
            x = screen->width - radius - 1;
            vx = -vx;
        }

        if (y - radius < 0)
        {
            y = radius;
            vy = -vy;
        }
        else if (y + radius >= screen->height)
        {
            y = screen->height - radius - 1;
            vy = -vy;
        }

        usleep(16666);
    }

    ScreenDestroy(&screen);

    return EXIT_SUCCESS;
}
#include "usdk.color.h"

void RGB2HSV(u8 r, u8 g, u8 b, f32* h, f32* s, f32* v)
{
    f32 cmax  = MAX3(r, g, b);
    f32 cmin  = MIN3(r, g, b);
    f32 delta = cmax - cmin;

    *v = cmax / 255.0 * 100.0;
    *s = cmax ? (delta / cmax) : 0;

    if (delta == 0) {
        *h = 0;
    } else if (cmax == r) {
        *h = 60 * ((g - b) / delta);
    } else if (cmax == g) {
        *h = 60 * ((b - r) / delta + 2);
    } else {
        *h = 60 * ((r - g) / delta + 4);
    }

    if (*h < 0) {
        *h += 360;
    }
}
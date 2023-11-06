#include <stdio.h>
#include <stdint.h>

#include "img.h"  // 44x44

void dispAsciiImgae(const uint8_t* image, uint16_t width, uint16_t height)
{
    const char table[] = "@B%%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    uint8_t  idx;
    uint16_t j;

    while (height--)
    {
        for (j = 0; j < width; ++j)
        {
            idx = ((sizeof(table) - 1) / 256.0f) * (*image++);
            putchar(table[idx]);
        }

        // putchar('\r');
        putchar('\n');
    }
}

int main()
{
    dispAsciiImgae(gImage_img, 110, 110);
}
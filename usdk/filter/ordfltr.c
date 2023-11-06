#include "usdk.basic.h"

/**
 * @brief n-order filter
 */
typedef struct {
    u8   n;  // the filter order
    f32* a;  // a[0] is offset,  a[i] is the denominator filter coefficient value for z^(-i)
    f32* b;  // the numerator filter coefficient value, b[i] for z^(-i)
    f32* x;  // the input value, x[i] at time sample n=-i
    f32* y;  // the output value, y[i] at time sample n=-i
} nOrderFilter_t;

/**

 * @brief first-order filter
   */
typedef struct {
    f32 a[1];
    f32 b[1];
    f32 x[1];
    f32 y[1];
} FirstOrderFilter_t;

/**
 * @brief second-order filter
 */
typedef struct {
    f32 a[2];
    f32 b[2];
    f32 x[2];
    f32 y[2];
} SecondOrderFilter_t;

/**
 * @brief third-order filter
 */
typedef struct {
    f32 a[3];
    f32 b[3];
    f32 x[3];
    f32 y[3];
} ThirdOrderFilter_t;

#define InitOrderFilter(filter, order) \
    {                                  \
        .n = order,                    \
        .a = filter->a,                \
        .b = filter->b,                \
        .x = filter->x,                \
        .y = filter->y,                \
    }

f32 nOrderFilter_Handler(nOrderFilter_t* obj, f32 input)
{
    u8 i;

    u8   n = obj->n;
    f32* a = obj->a;
    f32* b = obj->b;
    f32* x = obj->x;
    f32* y = obj->y;

    for (i = n - 1; i > 0; --i)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    x[0] = input;
    y[0] = 0.f;

    // Σa[1:n-1] + Σb[0:n-1] = 1
    for (i = 0; i < n; ++i)
    {
        y[0] += a[i] * y[i];
        y[0] += b[i] * x[i];
    }

    // add bias
    f32 output = y[0] + a[0];

    return output;
}

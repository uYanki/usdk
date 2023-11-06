#include "usdk.basic.h"

// 逐点

typedef struct {
    // filter
    f32  sum;
    u16  order;  // 阶数
    u16  width;
    // ringbuf
    u16  index;
    f32* buffer;  // 缓冲区
} avg_fltr_t;

void avg_fltr_init(avg_fltr_t* filter, f32 buffer[], u16 order)
{
    filter->sum    = 0;
    filter->order  = order;
    filter->width  = 0;
    filter->index  = 0;
    filter->buffer = buffer;
}

f32 avg_fltr_proc(avg_fltr_t* filter, f32 input)
{
    u16 index = filter->index;

    if (filter->width < filter->order)
    {
        filter->width++;
    }
    else
    {
        filter->sum -= filter->buffer[filter->index];
    }

    filter->sum += (filter->buffer[filter->index++] = input);

    if (filter->index == filter->order)
    {
        filter->index = 0;
    }

    return filter->sum / filter->width;
}

// 批量

f32 AverageFilter_Handler(f32 input[], f32 output[], u16 count, u16 order)
{
    f32 sum   = 0;
    u16 width = 0;

    while (width < order)
    {
        width++;

        sum += *input;
        *output = sum / width;

        input++;
        output++;
    }

    count -= order;

    while (count > 0)
    {
        count--;

        sum -= *(input - width);
        sum += *input;
        *output = sum / width;

        input++;
        output++;
    }
}

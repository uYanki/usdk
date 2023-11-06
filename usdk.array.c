#include <stdio.h>
#include <stdarg.h>
#include "usdk.array.h"

boolean_e arr2csv(str filepath, csv_col_t data[], u16 rows, u16 cols)
{
    u16 row, col;
    if (rows == 0 || cols == 0) {
        return FALSE;
    }

    FILE* fp = fopen(filepath, "w");
    if (fp == nullptr) {
        return FALSE;
    }

    col = 0;
    while (col < cols) {
        fprintf(fp, "%s", data[col].header);
        fputc((++col < cols) ? ',' : '\n', fp);
    }

    for (row = 0; row < rows; ++row) {
        col = 0;
        while (col < cols) {
            str   format = data[col].format;
            void* array  = data[col].array;
            if (array && format) {
                // clang-format off
                switch (data[col].type) {
                    case DATA_TYPE_S8  : fprintf(fp, format, ((s8* )(array))[row]); break;
                    case DATA_TYPE_S16 : fprintf(fp, format, ((s16*)(array))[row]); break;
                    case DATA_TYPE_S32 : fprintf(fp, format, ((s32*)(array))[row]); break;
                    case DATA_TYPE_S64 : fprintf(fp, format, ((s64*)(array))[row]); break;
                    case DATA_TYPE_U8  : fprintf(fp, format, ((u8* )(array))[row]); break;
                    case DATA_TYPE_U16 : fprintf(fp, format, ((u16*)(array))[row]); break;
                    case DATA_TYPE_U32 : fprintf(fp, format, ((u32*)(array))[row]); break;
                    case DATA_TYPE_U64 : fprintf(fp, format, ((u64*)(array))[row]); break;
                    case DATA_TYPE_F32 : fprintf(fp, format, ((f32*)(array))[row]); break;
                    case DATA_TYPE_F64 : fprintf(fp, format, ((f64*)(array))[row]); break;
                    case DATA_TYPE_STR : fprintf(fp, format, ((s8**)(array))[row]); break;
                }
                // clang-format on
            }
            fputc((++col < cols) ? ',' : '\n', fp);
        }
    }

    fclose(fp);

    return TRUE;
}

#if 0

int main()  // test
{
    f64   x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    f64   y[] = {2.0, 4.0, 6.0, 8.0, 10.0};
    u32   z[] = {3, 6, 9, 12, 15};
    char* k[] = {"ss", "ss", "sad0", "ssa", "ss"};

    csv_col_t cols[] = {
        {.header = "A", .format = "%.2f", .array = x, .type = DATA_TYPE_F64},
        {.header = "B", .format = "%.2f", .array = y, .type = DATA_TYPE_F64},
        {.header = "C", .format = "%d",   .array = z, .type = DATA_TYPE_U32},
        {.header = "D", .format = "%s",   .array = k, .type = DATA_TYPE_STR},
    };

    arr2csv("data.csv", cols, ARRAY_SIZE(x), ARRAY_SIZE(cols));

    return 0;
}

#endif

f32 array_sum(f32* arr, u16 cnt)
{
    f32 sum = 0;

    while (cnt--) {
        sum += arr[cnt];
    }

    return sum;
}

void array_scale(f32* arr, u16 cnt, f32 offset)
{
    while (cnt--) {
        arr[cnt] += offset;
    }
}

void array_offset(f32* arr, u16 cnt, f32 scale)
{
    while (cnt--) {
        arr[cnt] *= scale;
    }
}

#if 0

// 不使用可变参数形式的累加
// 因为输入的参数需全为同种类型参数
// 且 va_arg 不支持 f32

// usage: printf("%lf\n", args_sumf(4, 1.0, 2.0, 3.0, 4.0));
f64 args_sumf(u32 cnt, f64 dat, ...)
{
    va_list ap;

    f64 sum = dat;

    va_start(ap, dat);
    while (--cnt) {
        // note: `va_arg` unsupport 32-bit float,
        //     only support 64-bit float
        sum += va_arg(ap, f64);
    }
    va_end(ap);

    return sum;
}

// uasge: printf("%d\n", args_sum(4, 1, 2, 3, 4));
s32 args_sum(u32 cnt, s32 dat, ...)
{
    va_list ap;

    s32 sum = dat;

    va_start(ap, dat);
    while (--cnt) {
        sum += va_arg(ap, s32);
    }
    va_end(ap);

    return sum;
}

#endif
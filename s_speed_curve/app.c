
#include "usdk.array.h"

typedef struct {
    f32 a0;  // 初加速度
    f32 v0;  // 初速度
    f32 s0;  // 初位移
    f32 j;   // 加加速度
    f32 a;   // 加速度
    f32 v;   // 速度
    f32 s;   // 位移
    f32 t;   // 时间
} curve_t;

void curve_doit(curve_t* curve, f32 dt)
{
    curve->t += dt;

    curve->a = curve->j * curve->t;      // a = j * t
    curve->v = curve->a * curve->t / 2;  // v = 1/2 * j * t^2
    curve->s = curve->v * curve->t / 3;  // s = 1/6 * j * t^3

    curve->a += curve->a0;
    curve->v += curve->v0;
    curve->s += curve->s0;

    curve->v += curve->a0 * curve->t;                 // v = a * t
    curve->s += curve->a0 * curve->t * curve->t / 2;  // s = 1/2 * a * t^2

    curve->s += curve->v0 * curve->t;
}

void curve_backup(curve_t* curve)
{
    curve->a0 = curve->a;
    curve->v0 = curve->v;
    curve->s0 = curve->s;
    curve->t  = 0;
    curve->j  = 0;
}

#define STEP 30

int main()
{
    u8 idx = 0;

    f32 arr_s[STEP * 7] = {0};
    f32 arr_v[STEP * 7] = {0};
    f32 arr_a[STEP * 7] = {0};
    f32 arr_j[STEP * 7] = {0};

    curve_t c = {0};

    int j[7] = {1, 0, -1, 0, -1, 0, 1};

    // S 曲线:
    // 匀加加速度
    // 匀加速度
    // 匀减减速度
    // 匀速
    // 匀减减速度
    // 匀减速度
    // 匀加加速度

    c.j = 0, c.a0 = 0, c.v0 = 0, c.s0 = 0, c.t = 0;

    for (int k = 0; k < ARRAY_SIZE(j); ++k) {
        curve_backup(&c);
        c.j = j[k], c.t = 0;
        for (int t = 0; t < STEP; ++t) {
            arr_s[idx] = c.s, arr_v[idx] = c.v, arr_a[idx] = c.a, arr_j[idx] = c.j;
            curve_doit(&c, 0.1);
            ++idx;
        }
    }

    array_scale(arr_j, ARRAY_SIZE(arr_j), 50, DATA_TYPE_F32);
    array_scale(arr_v, ARRAY_SIZE(arr_v), 10, DATA_TYPE_F32);
    array_scale(arr_a, ARRAY_SIZE(arr_a), 50, DATA_TYPE_F32);

    csv_col_t cols[] = {
        {.header = "s", .format = "%.2f", .array = arr_s, .type = DATA_TYPE_F32},
        {.header = "v", .format = "%.2f", .array = arr_v, .type = DATA_TYPE_F32},
        {.header = "a", .format = "%.2f", .array = arr_a, .type = DATA_TYPE_F32},
        {.header = "j", .format = "%.2f", .array = arr_j, .type = DATA_TYPE_F32},
    };

    arr2csv("data.csv", cols, ARRAY_SIZE(arr_s), ARRAY_SIZE(cols));

    return 0;
}
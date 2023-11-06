#include "usdk.h"

f32 _inv_sqrtf(f32 v)
{
    // 单精度浮点开平方的倒数运算

    f32 fv = 0.5f * v;
    s32 uv = *(s32*)&v;

    uv = 0x5f3759df - (uv >> 1);
    v  = *(f32*)&uv;
    v  = v * (1.5f - (fv * v * v));

    return v;
}

f32 _sqrtf(f32 v)
{
    // 单精度浮点开平方运算

    f32 fv = v;
    u32 uv = *(u32*)&v;

    uv = (uv + 0x3f76cf62) >> 1;
    v  = *(f32*)&uv;
    v  = (v + fv / v) * 0.5;

    return v;
}
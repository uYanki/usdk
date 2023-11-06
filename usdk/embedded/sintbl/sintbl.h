#ifndef __USDK_SINE_H__
#define __USDK_SINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "usdk.h"

///< 查表法, 分辨率 0.35°
void get_sin_cos(__IN s16 angle, __OUT f32* sin, __OUT f32* cos);

#ifdef __cplusplus
}
#endif

#endif
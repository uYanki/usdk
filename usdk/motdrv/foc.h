
#ifndef __MOTDRV_FOC_H__
#define __MOTDRV_FOC_H__

#include "usdk.h"

typedef struct {
    f32 phase_a;  // phase-a stator
    f32 phase_b;  // phase-b stator
    f32 phase_c;  // phase-c stator

    f32 alpha;  // stationary d-axis stator
    f32 beta;   // stationary q-axis stator
} clarke_t;

typedef struct {
    f32 alpha;  // stationary d-axis stator
    f32 beta;   // stationary q-axis stator
    f32 theta;  // rotating angle (electrical angle)

    f32 d;  // rotating d-axis stator variable
    f32 q;  // rotating q-axis stator variable

    f32 sin;  // sine(theta)
    f32 cos;  // cosine(theta)
} park_t;

typedef struct {
    f32 Ualpha;  // alpha-axis phase voltage
    f32 Ubeta;   // beta-axis phase voltage

    f32 Ta;  // phase-a switching function
    f32 Tb;  // phase-b switching function
    f32 Tc;  // phase-c switching function

    u8 Sector;  // Space vector sector
} svgen_t;

void park(park_t* v);
void ipark(park_t* v);

void clarke(clarke_t* v);
void iclarke(clarke_t* v);
void svgen(svgen_t* v);

#endif
#include "foc.h"

/**
 * @brief Park Transformation
 * @param [in] alpha, beta
 * @param [out] d, q
 */
void park(park_t* v)
{
    v->d = v->beta * v->sin + v->alpha * v->cos;
    v->q = v->beta * v->cos - v->alpha * v->sin;
}

/**
 * @brief Inverse Park Transformation
 * @param [in] d, q
 * @param [out] alpha, beta
 */
void ipark(park_t* v)
{
    v->alpha = v->d * v->cos - v->q * v->sin;
    v->beta  = v->d * v->sin + v->q * v->cos;
}

/**
 * @brief Clarke Transformation
 * @param [in] phase_a, phase_b, phase_c
 * @param [out] alpha, beta
 */
void clarke(clarke_t* v)
{
    v->alpha = v->phase_a;
    v->beta  = (v->phase_a + v->phase_b * 2) * M_INVSQRT3;
}

/**
 * @brief Inverse Clarke Transformation
 * @param [in] alpha, beta
 * @param [out] phase_a, phase_b, phase_c
 */
void iclarke(clarke_t* v)
{
    v->phase_a = v->alpha;
    v->phase_b = +0.5f * (M_SQRT3 * v->beta - v->alpha);
    v->phase_c = -0.5f * (M_SQRT3 * v->beta + v->alpha);
}

/**
 * @brief Space Vector PWM Generator
 *
 * @param [in] Ualpha, Ubeta
 * @param [out] Ta, Tb, Tc, Sector
 */
void svgen(svgen_t* v)
{
    f32 X = v->Ubeta;
    f32 Y = (v->Ubeta + M_SQRT3 * v->Ualpha) * 0.5f;
    f32 Z = Y - X;

    v->Sector = 3;

    if (Y > 0)
    {
        v->Sector -= 1;
    }
    if (Z > 0)
    {
        v->Sector -= 1;
    }
    if (X < 0)
    {
        v->Sector = 7 - v->Sector;
    }

    switch (v->Sector)
    {
        case 1:
        case 4: {
            v->Ta = Y;
            v->Tb = X - Z;
            v->Tc = -Y;
            break;
        }
        case 2:
        case 5: {
            v->Ta = Z + Y;
            v->Tb = X;
            v->Tc = -X;
            break;
        }
        default:
        case 3:
        case 6: {
            v->Ta = Z;
            v->Tb = -Z;
            v->Tc = -(X + Y);
            break;
        }
    }
}

/**
 * @brief
 *
 * @param MechTheta Motor Electrical angle
 * @param PolePairs Number of pole pairs
 *
 * @return Motor Mechanical Angle
 */
f32 angle_gen(f32 MechTheta, f32 PolePairs)
{
    f32 ElecTheta = PolePairs * MechTheta;

    while (ElecTheta > 6.28f)
    {
        ElecTheta -= 6.28f;
    }

    return ElecTheta;
}

#if 0

void foc_tst()
{
#if 1

    if (keyflg & BV(0))
    {
        mechAngle += 0.002;

        if (mechAngle > 6.28)
        {
            mechAngle = 0;
        }
    }
    else
    {
        mechAngle -= 0.002;

        if (mechAngle < 0)
        {
            mechAngle = 6.28;
        }
    }

    elecAngle = mechAngle * polepairs;
#else

    if (keyflg & BV(0))
    {
        elecAngle += 0.01;
    }
    else
    {
        elecAngle -= 0.01;
    }

#endif

    _park.sin = sinf(elecAngle);
    _park.cos = cosf(elecAngle);

    ipark(&_park);

    _svpwm.Ualpha = _park.alpha;
    _svpwm.Ubeta  = _park.beta;

    svgen(&_svpwm);

    DUTY_A = _svpwm.Ta;
    DUTY_B = _svpwm.Tb;
    DUTY_C = _svpwm.Tc;
}

#endif
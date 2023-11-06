#ifndef __USDK_BASIC_H__
#define __USDK_BASIC_H__

#define UNUSED(x) ((void)(x))

//-----------------------------------------------------------------------------
// Modifiers
//

#define RW        ///< read write
#define RO const  ///< read only
#define WO        ///< write only

#define __IN   ///< input
#define __OUT  ///< output
#define __INOUT

// #define UNUSED(x)   ((void)(x))
#define UNUSED(...) (void)(__VA_ARGS__)

//-----------------------------------------------------------------------------
// Types
//

typedef signed char      s8;
typedef signed short     s16;
typedef signed long      s32;
typedef signed long long s64;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;

typedef float  f32;
typedef double f64;
// typedef long double f64;

//---------------------------------------------------------

#if 0

// clang-format off

typedef s8     int8_t,    INT8;
typedef s16   int16_t,   INT16;
typedef s32   int32_t,   INT32;
typedef s64   int64_t,   INT64;
typedef u8    uint8_t,   UINT8;
typedef u16  uint16_t,  UINT16;
typedef u32  uint32_t,  UINT32;
typedef u64  uint64_t,  UINT64;
typedef f32 float32_t, FLOAT32;
typedef f64 float64_t, FLOAT64;

// clang-format on

typedef int          INT;
typedef unsigned int UINT;

#endif

//---------------------------------------------------------

#if 0

typedef u8  BYTE;  ///< single
typedef u16 WORD;
typedef u32 DWORD;  ///< double
typedef u64 QWORD;  ///< quad
typedef f32 REAL;

#endif

//---------------------------------------------------------

#define REG volatile  ///< register

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

#define REG8U(addr)  *(u8*)(addr)
#define REG16U(addr) *(u16*)(addr)
#define REG32U(addr) *(u32*)(addr)
#define REG64U(addr) *(u64*)(addr)

#define REG8S(addr)  *(s8*)(addr)
#define REG16S(addr) *(s16*)(addr)
#define REG32S(addr) *(s32*)(addr)
#define REG64S(addr) *(s64*)(addr)

//---------------------------------------------------------

/**
 * @note
 *
 * f32 = pow(-1,sign) * (1+mag) * pow(2,exp-127)
 * f64 = pow(-1,sign) * (1+mag) * pow(2,exp-1023)
 *
 */

typedef union {
    f32 all;
    struct {
        u32 mag  : 23;  // 小数位
        u32 exp  : 8;   // 指数位
        u32 sign : 1;   // 符号位
    } bit;
} f32u;

typedef union {
    f64 all;
    struct {
        u64 mag  : 52;
        u64 exp  : 11;
        u64 sign : 1;
    } bit;
} f64u;

//---------------------------------------------------------
// boolean

#if 1
#include <stdbool.h>
#else
#define bool  char
#define true  1
#define false 0
#endif

//---------------------------------------------------------
// Enums

#if 1
typedef enum {
    FALSE = 0U,
    TRUE  = !FALSE,
} bool_e;
#endif

#if 1
typedef enum {
    RESET = 0U,
    SET   = !RESET,
} state_e;
#endif

#if 1
typedef enum {
    DISABLE = 0U,
    ENABLE  = !DISABLE
} enable_e;
#endif

#if 1
typedef enum {
    OFF = 0U,
    ON  = !OFF,
} switch_e;
#endif

#if 1
typedef enum {
    FAILURE = 0U,
    SUCCESS = !FAILURE,
} result_e;
#endif

#if 1
typedef enum {
    DIR_CCW = 0U,        ///< Clockwise, 顺时针
    DIR_CW  = !DIR_CCW,  ///< Counterclockwise, 逆时针
} direction_e;
#endif

#if 1
typedef enum {
    ONESHOT    = 0U,  ///< 单次
    CONTINUOUS = 1U,  ///< 连续
} times_e;
#endif

//-----------------------------------------------------------------------------
// Constants
//

#ifndef NULL
#define NULL 0
#endif

#ifndef nullptr
#define nullptr ((void*)0)
#endif

//---------------------------------------------------------

#define S8_MIN                                     (s8)0x80                 ///< -128
#define S16_MIN                                    (s16)0x8000              ///< -32678
#define S32_MIN                                    (s32)0x80000000          ///< -2147483648
#define S64_MIN                                    (s64)0x8000000000000000  ///< -9223372036854775808

#define S8_MAX                                     (s8)0x7F                 ///< +127
#define S16_MAX                                    (s16)0x7FFF              ///< +32767
#define S32_MAX                                    (s32)0x7FFFFFFF          ///< +2147483647
#define S64_MAX                                    (s64)0x7FFFFFFFFFFFFFFF  ///< +9223372036854775807

#define U8_MAX                                     (u8)0xFF                 ///< +255
#define U16_MAX                                    (u16)0xFFFF              ///< +65535
#define U32_MAX                                    (u32)0xFFFFFFFF          ///< +4294967295
#define U64_MAX                                    (u64)0xFFFFFFFFFFFFFFFF  ///< +18446744073709551615

#define F32_MIN                                    1.17549435e-38f
#define F64_MIN                                    2.2250738585072014e-308

#define F32_MAX                                    3.40282347e+38f
#define F64_MAX                                    1.7976931348623157e+308

//---------------------------------------------------------

#define M_PI                                       3.1415926f  ///< 圆周率   π = 3.14159265358979323846
#define M_E                                        2.7182818f  ///< 自然常数 e = 2.71828182845904523536 = (1+1/n)^n
#define M_PHI                                      1.618033f   ///< 黄金比例 φ = 1.61803398874989484820 = (1+sqrt(5))/2

#define M_PI_X2                                    6.2831852f  ///< 2π
#define M_PI_X100                                  314         ///< 100π

#define M_LOG2E                                    1.4426950f  // log2(e) = 1.44269504088896340736
#define M_LOG10E                                   0.4342944f  // log10(e) = 0.434294481903251827651
#define M_LN2                                      0.6931471f  // ln(2) = 0.693147180559945309417
#define M_LN10                                     2.3025850f  // ln(10) = 2.30258509299404568402

#define M_RAD2DGE                                  57.295779f  ///< 1 radians to 57.295780 degress
#define M_DEG2RAD                                  0.017453f   ///< 1 degress to  0.017453 radians

#define M_SIN15                                    0.258819f
#define M_SIN30                                    0.5f
#define M_SIN45                                    0.707106f  ///< sqrt(2)/2
#define M_SIN60                                    0.866025f  ///< sqrt(3)/2
#define M_SIN75                                    0.965925f

#define M_COS15                                    SIN75
#define M_COS30                                    SIN60
#define M_COS45                                    SIN45
#define M_COS60                                    SIN30
#define M_COS75                                    SIN15

#define M_SQRT2                                    1.414213f
#define M_SQRT3                                    1.732050f
#define M_SQRT5                                    2.236067f
#define M_INVSQRT2                                 0.707106f  ///< 1/sqrt(2)
#define M_INVSQRT3                                 0.577350f  ///< 1/sqrt(3)
#define M_INVSQRT5                                 0.447213f  ///< 1/sqrt(5)

//-----------------------------------------------------------------------------
// Macros
//

/**
 * @param lhs: left-hand side
 * @param rhs: right-hand side
 */
#define MIN(lhs, rhs)                              (((lhs) < (rhs)) ? (lhs) : (rhs))
#define MAX(lhs, rhs)                              (((lhs) > (rhs)) ? (lhs) : (rhs))

#define MIN3(a, b, c)                              (MIN(a, MIN(b, c)))
#define MAX3(a, b, c)                              (MAX(a, MAX(b, c)))

/**
 * @param lo: lowest allowable value
 * @param hi: highest allowable value
 */
#define CLAMP(val, lo, hi)                         (MAX(lo, MIN(val, hi)))
#define INOPEN(val, lo, hi)                        (((lo) < (val)) && ((val) < (hi)))    ///< check if the val is within the open range
#define INCLOSE(val, lo, hi)                       (((lo) <= (val)) && ((val) <= (hi)))  ///< check if the val is within the closed range

/**
 *              OutMax - OutMin
 *  outVal  = -------------------  x  ( inVal - inMin ) + outMin
 *               inMax - inMin
 */
#define MapTo(inVal, inMin, inMax, outMin, outMax) ((((outMax) - (outMin)) / (f32)((inMax) - (inMin))) * ((inVal) - (inMin)) + (outMin))

//---------------------------------------------------------

///< val of elements in an array
#define ARRAY_SIZE(array)                          (sizeof(array) / sizeof(*(array)))
///< byte offset of member in structure (OFFSETOF)
#define MEMBER_OFFSET(structure, member)           ((u32)(char*)&(((structure*)0)->member))
///< size of a member of a structure
#define MEMBER_SIZE(structure, member)             (sizeof(((structure*)0)->member))

//---------------------------------------------------------

/**
 * @brief swap integer variable
 * @note  when rhs and lhs are equal, the XOR result of rhs and lhs is 0.
 */
#define SWAP_INT(lhs, rhs)                            \
    do {                                              \
        if (lhs != rhs) { lhs ^= rhs ^= lhs ^= rhs; } \
    } while (0)

///< swap variable
#define SWAP_ANY(type, lhs, rhs) \
    do {                         \
        type tmp;                \
        tmp   = (lhs);           \
        (lhs) = (rhs);           \
        (rhs) = tmp;             \
    } while (0)

//---------------------------------------------------------

#ifndef BV
#define BV(n) (1UL << (n))
#endif

#define MASK8(LEN)               (~(U8_MAX << (LEN)))
#define MASK16(LEN)              (~(U16_MAX << (LEN)))
#define MASK32(LEN)              (~(U32_MAX << (LEN)))
#define MASK64(LEN)              (~(U64_MAX << (LEN)))

// @note STB: start bit

#define SETBIT(DAT, BIT)         ((DAT) |= (1UL << (BIT)))           ///< set a bit (bit-32)
#define CLRBIT(DAT, BIT)         ((DAT) &= (~(1UL << (BIT))))        ///< clear a bit (bit-32)
#define INVBIT(DAT, BIT)         ((DAT) ^= (1UL << (BIT)))           ///< invert a bit (bit-32)
#define GETBIT(DAT, BIT)         (((DAT) >> (BIT)) & 0x1)            ///< get a bit (bit-32/64)
#define SETBITS(DAT, STB, LEN)   ((DAT) |= (MASK32(LEN) << (STB)))   ///< set bits (bit-32)
#define CLRBITS(DAT, STB, LEN)   ((DAT) &= ~(MASK32(LEN) << (STB)))  ///< clear bits (bit-32)
#define INVBITS(DAT, STB, LEN)   ((DAT) ^= (MASK32(LEN) << (STB)))   ///< invert bits (bit-32)
#define GETBITS(DAT, STB, LEN)   (((DAT) >> (STB)) & MASK32(LEN))    ///< get bits (bit-32)

#define SETBIT64(DAT, BIT)       ((DAT) |= (1ULL << (BIT)))     ///< set a bit (bit-64)
#define CLRBIT64(DAT, BIT)       ((DAT) &= (~(1ULL << (BIT))))  ///< clear a bit (bit-64)
#define INVBIT64(DAT, BIT)       ((DAT) ^= (1ULL << (BIT)))     ///< invert a bit (bit-64)

#define LOBYTE(DAT)              (0xFF & (DAT))
#define HIBYTE(DAT)              (0xFF & ((DAT) >> 8))
#define LOWORD(DAT)              (0xFFFF & (DAT))
#define HIWORD(DAT)              (0xFFFF & ((DAT) >> 16))

///< link two 16bits data to a 32bits data
#define LINK32(HI, LO)           (((u32)(HI) << 16) | ((u16)(LO)))
///< link two 32bits data to a 64bits data
#define LINK64_2(HI, LO)         (((u64)(HI) << 32) | ((u32)(LO)))
///< link four 16bits data to a 64bits data
#define LINK64_4(W3, W2, W1, W0) (((u64)(W3) << 48) | ((u64)(W2) << 32) | ((u64)(W1) << 16) | ((u64)(W0)))

//-----------------------------------------------------------------------------
// color
//

#define RGB(r, g, b)             ((0xFF & (r)) << 16 | (0xFF & (g)) << 8 | (0xFF & (b)))
#define BGR(b, g, r)             ((0xFF & (b)) << 16 | (0xFF & (g)) << 8 | (0xFF & (r)))

#define RGB2BGR(rgb)             (((0xFF0000 & (rgb)) >> 16) | (0x00FF00 & (rgb)) | ((0x0000FF & (rgb)) << 16))
#define BGR2RGB(bgr)             (((0xFF0000 & (bgr)) >> 16) | (0x00FF00 & (bgr)) | ((0x0000FF & (bgr)) << 16))

//-----------------------------------------------------------------------------
// sleep
//

#if 0

typedef u32 tick_t;

typedef enum {
    UNIT_US = 1ull,
    UNIT_MS = 1000ull,
    UNIT_S  = 1000000ull,
} DelayUnit_e;

void DelayInit(void);
void DelayBlock(tick_t nWaitTime);
bool DelayNonBlock(tick_t nStartTick, tick_t nWaitTime);
void FirewareDelay(tick_t nWaitTime);

#endif

#endif
